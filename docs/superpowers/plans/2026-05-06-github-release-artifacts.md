# GitHub Release Artifact Generation Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Create a GitHub Actions workflow that automatically builds and releases cdocx library binaries (static + shared) for Windows (MSVC) and Linux (GCC) on GitHub Release when a version tag is pushed.

**Architecture:** A single `.github/workflows/release.yml` file with matrix-based parallel builds. Each platform job builds static and shared libraries, packages them with headers into a platform archive, and uploads as artifacts. A final `release` job downloads all artifacts and attaches them to a GitHub Release.

**Tech Stack:** GitHub Actions, CMake, MSVC 2022 (Windows), GCC (Linux), zip/tar.gz

---

## File Structure

| File | Action | Purpose |
|------|--------|---------|
| `.github/workflows/release.yml` | Create | Main workflow: triggers on tag, builds all platforms, creates GitHub Release |

---

## Task 1: Create the Release Workflow File

**Files:**
- Create: `.github/workflows/release.yml`

- [ ] **Step 1: Write the workflow trigger and global configuration**

  ```yaml
  name: Release Artifacts

  on:
    push:
      tags:
        - 'v*.*.*'

  env:
    PACKAGE_NAME: cdocx
  ```

  This triggers on any tag matching `v*.*.*` (e.g., `v0.9.0`).

- [ ] **Step 2: Add the version extraction job (shared logic)**

  ```yaml
  jobs:
    extract-version:
      runs-on: ubuntu-latest
      outputs:
        version: ${{ steps.get_version.outputs.version }}
      steps:
        - name: Extract version from tag
          id: get_version
          run: echo "version=${GITHUB_REF_NAME#v}" >> "$GITHUB_OUTPUT"
  ```

  This extracts `0.9.0` from `refs/tags/v0.9.0` and makes it available to all downstream jobs via `needs.extract-version.outputs.version`.

- [ ] **Step 3: Commit the base structure**

  ```bash
  git add .github/workflows/release.yml
  git commit -m "feat(ci): add release artifact workflow scaffolding

  Sets up tag-triggered workflow with version extraction.

  Co-Authored-By: Claude Opus 4.7 (1M context) <noreply@anthropic.com>"
  ```

---

## Task 2: Implement Windows Build Job

**Files:**
- Modify: `.github/workflows/release.yml`

- [ ] **Step 1: Add the Windows build job with matrix for Release/Debug**

  Append this job to the `jobs:` section:

  ```yaml
    build-windows:
      needs: extract-version
      runs-on: windows-2022
      strategy:
        matrix:
          config: [Release, Debug]
      steps:
        - name: Checkout
          uses: actions/checkout@v4
          with:
            submodules: recursive

        - name: Setup MSVC
          uses: microsoft/setup-msbuild@v2

        - name: Build static library
          run: |
            cmake -B build_static `
              -G "Visual Studio 17 2022" `
              -A x64 `
              -DBUILD_SHARED_LIBS=OFF `
              -DBUILD_TESTING=OFF `
              -DBUILD_EXAMPLES=OFF
            cmake --build build_static --config ${{ matrix.config }} --parallel

        - name: Build shared library
          run: |
            cmake -B build_shared `
              -G "Visual Studio 17 2022" `
              -A x64 `
              -DBUILD_SHARED_LIBS=ON `
              -DBUILD_TESTING=OFF `
              -DBUILD_EXAMPLES=OFF
            cmake --build build_shared --config ${{ matrix.config }} --parallel

        - name: Package artifacts
          shell: pwsh
          run: |
            $version = "${{ needs.extract-version.outputs.version }}"
            $config = "${{ matrix.config }}".ToLower()
            $staging = "cdocx-$version-windows-msvc-x64-$config"
            New-Item -ItemType Directory -Path "$staging/include/cdocx" -Force
            New-Item -ItemType Directory -Path "$staging/lib" -Force

            # Copy headers from source
            Copy-Item -Path "include/cdocx.h" -Destination "$staging/include/"
            Copy-Item -Path "include/cdocx/*.h" -Destination "$staging/include/cdocx/"

            # Copy static library (rename to avoid conflict with import lib)
            Copy-Item -Path "build_static/${{ matrix.config }}/cdocx.lib" -Destination "$staging/lib/cdocx_static.lib"

            # Copy shared library (import lib + DLL)
            Copy-Item -Path "build_shared/${{ matrix.config }}/cdocx.lib" -Destination "$staging/lib/cdocx.lib"
            Copy-Item -Path "build_shared/${{ matrix.config }}/cdocx.dll" -Destination "$staging/lib/cdocx.dll"

            # Create zip
            Compress-Archive -Path "$staging/*" -DestinationPath "$staging.zip"

        - name: Upload artifact
          uses: actions/upload-artifact@v4
          with:
            name: windows-${{ matrix.config }}
            path: cdocx-*-windows-msvc-x64-*.zip
  ```

  **Key decisions documented:**
  - Static library is renamed to `cdocx_static.lib` because CMake names both static and import libraries `cdocx.lib` by default. Without renaming, they would overwrite each other.
  - Headers are copied directly from `include/` source directory to ensure correct paths (`include/cdocx.h` and `include/cdocx/*.h`), avoiding the path flattening issue that `cmake --install` would cause.
  - `BUILD_TESTING=OFF` and `BUILD_EXAMPLES=OFF` reduce build time since we only need the library.

- [ ] **Step 2: Commit the Windows build job**

  ```bash
  git add .github/workflows/release.yml
  git commit -m "feat(ci): add Windows build job for release artifacts

  Builds static (/MT) and shared (/MD) libraries on MSVC 2022,
  packages with headers into platform zip.

  Co-Authored-By: Claude Opus 4.7 (1M context) <noreply@anthropic.com>"
  ```

---

## Task 3: Implement Linux Build Job

**Files:**
- Modify: `.github/workflows/release.yml`

- [ ] **Step 1: Add the Linux build job with matrix for Release/Debug**

  Append this job to the `jobs:` section:

  ```yaml
    build-linux:
      needs: extract-version
      runs-on: ubuntu-latest
      strategy:
        matrix:
          config: [Release, Debug]
      steps:
        - name: Checkout
          uses: actions/checkout@v4
          with:
            submodules: recursive

        - name: Install dependencies
          run: |
            sudo apt-get update
            sudo apt-get install -y cmake ninja-build

        - name: Build static library
          run: |
            cmake -B build_static \
              -G Ninja \
              -DCMAKE_BUILD_TYPE=${{ matrix.config }} \
              -DBUILD_SHARED_LIBS=OFF \
              -DBUILD_TESTING=OFF \
              -DBUILD_EXAMPLES=OFF
            cmake --build build_static --parallel

        - name: Build shared library
          run: |
            cmake -B build_shared \
              -G Ninja \
              -DCMAKE_BUILD_TYPE=${{ matrix.config }} \
              -DBUILD_SHARED_LIBS=ON \
              -DBUILD_TESTING=OFF \
              -DBUILD_EXAMPLES=OFF
            cmake --build build_shared --parallel

        - name: Package artifacts
          run: |
            version="${{ needs.extract-version.outputs.version }}"
            config=$(echo "${{ matrix.config }}" | tr '[:upper:]' '[:lower:]')
            staging="cdocx-${version}-linux-gcc-x64-${config}"
            mkdir -p "${staging}/include/cdocx"
            mkdir -p "${staging}/lib"

            # Copy headers from source
            cp include/cdocx.h "${staging}/include/"
            cp include/cdocx/*.h "${staging}/include/cdocx/"

            # Copy static library
            cp build_static/libcdocx.a "${staging}/lib/"

            # Copy shared library
            cp build_shared/libcdocx.so "${staging}/lib/"

            # Create tar.gz
            tar czf "${staging}.tar.gz" "${staging}"

        - name: Upload artifact
          uses: actions/upload-artifact@v4
          with:
            name: linux-${{ matrix.config }}
            path: cdocx-*-linux-gcc-x64-*.tar.gz
  ```

  **Key decisions documented:**
  - Linux uses single-config Ninja generator, so `CMAKE_BUILD_TYPE` controls Release vs Debug.
  - Shared library on Linux produces `libcdocx.so` (no import lib needed like Windows).
  - Static and shared library names are naturally distinct (`libcdocx.a` vs `libcdocx.so`), no renaming needed.

- [ ] **Step 2: Commit the Linux build job**

  ```bash
  git add .github/workflows/release.yml
  git commit -m "feat(ci): add Linux build job for release artifacts

  Builds static (.a) and shared (.so) libraries on GCC,
  packages with headers into platform tar.gz.

  Co-Authored-By: Claude Opus 4.7 (1M context) <noreply@anthropic.com>"
  ```

---

## Task 4: Implement Release Creation Job

**Files:**
- Modify: `.github/workflows/release.yml`

- [ ] **Step 1: Add the release job that collects all artifacts**

  Append this job to the `jobs:` section:

  ```yaml
    release:
      needs: [extract-version, build-windows, build-linux]
      runs-on: ubuntu-latest
      steps:
        - name: Download all artifacts
          uses: actions/download-artifact@v4
          with:
            path: artifacts
            pattern: "*"
            merge-multiple: true

        - name: List artifacts
          run: ls -la artifacts/

        - name: Create GitHub Release
          uses: softprops/action-gh-release@v1
          with:
            name: ${{ github.ref_name }}
            files: artifacts/*
            generate_release_notes: true
          env:
            GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
  ```

  **Key decisions documented:**
  - The `release` job depends on all build jobs succeeding.
  - `actions/download-artifact@v4` downloads all artifacts from previous jobs.
  - `merge-multiple: true` puts all files directly into `artifacts/` without subdirectories.
  - `softprops/action-gh-release@v1` creates the Release and uploads the files.
  - `generate_release_notes: true` auto-generates release notes from commits since last tag.

- [ ] **Step 2: Commit the release job**

  ```bash
  git add .github/workflows/release.yml
  git commit -m "feat(ci): add GitHub Release creation job

  Collects all platform artifacts and attaches them to
  an auto-generated GitHub Release on tag push.

  Co-Authored-By: Claude Opus 4.7 (1M context) <noreply@anthropic.com>"
  ```

---

## Task 5: Validate the Workflow

**Files:**
- Test: `.github/workflows/release.yml`

- [ ] **Step 1: Validate YAML syntax**

  Run:
  ```bash
  python3 -c "import yaml; yaml.safe_load(open('.github/workflows/release.yml'))" && echo "YAML valid"
  ```
  Expected: `YAML valid` with no errors.

  Alternative if Python yaml not available:
  ```bash
  cat .github/workflows/release.yml | head -5
  ```
  Expected: First 5 lines of the file printed, confirming the file exists and is readable.

- [ ] **Step 2: Verify workflow file structure**

  Run:
  ```bash
  grep -c "^  " .github/workflows/release.yml
  ```
  Expected: A number > 0 (indicating indented YAML content exists).

  Run:
  ```bash
  grep -E "jobs:|build-windows:|build-linux:|release:" .github/workflows/release.yml
  ```
  Expected: Lines showing all 4 jobs are present.

- [ ] **Step 3: Commit validation result**

  If validation passes, no additional changes needed. The workflow is ready.

  ```bash
  git log --oneline -5
  ```
  Expected: Shows the 4 commits from Tasks 1-4.

---

## Spec Coverage Check

| Spec Requirement | Implementing Task |
|-----------------|-------------------|
| Trigger on `v*.*.*` tag push | Task 1, Step 1 |
| Extract version from tag | Task 1, Step 2 |
| Windows MSVC 2022 x64, Release + Debug | Task 2 |
| Linux GCC x64, Release + Debug | Task 3 |
| Static + shared in each package | Task 2, Step 1; Task 3, Step 1 |
| Headers included in package | Task 2, Step 1; Task 3, Step 1 |
| Windows zip format | Task 2, Step 1 (`Compress-Archive`) |
| Linux tar.gz format | Task 3, Step 1 (`tar czf`) |
| Upload to GitHub Release | Task 4, Step 1 |
| Auto-generated release notes | Task 4, Step 1 (`generate_release_notes: true`) |
| Windows static lib rename to avoid conflict | Task 2, Step 1 (`Copy-Item ... cdocx_static.lib`) |

---

## Known Limitations (Documented)

1. **CMake config not included**: The auto-generated `cdocx-config.cmake` from `install(EXPORT)` references `pugixml::pugixml` and `zip::zip`, requiring users to also install those dependencies. Since pugixml and zip are FetchContent dependencies built alongside cdocx, distributing a standalone CMake config is non-trivial. Users should manually specify include paths and link libraries.

2. **Windows DLL self-contained**: The Windows `cdocx.dll` includes pugixml and zip code statically linked, so end users only need `cdocx.dll` + `cdocx.lib` (import lib) at runtime.

3. **Linux shared library dependencies**: The Linux `libcdocx.so` may still require `libpugixml.so` and `libzip.so` at runtime (depending on CMake configuration). For fully standalone deployment, consider static linking on Linux.

4. **No macOS**: Per user requirement, macOS is intentionally excluded from this workflow.
