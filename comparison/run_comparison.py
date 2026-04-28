#!/usr/bin/env python3
"""
Unified comparison runner for cdocx vs python-docx.
Generates reference documents, builds cdocx equivalents, runs analysis,
and produces a summary report.
"""

import subprocess
import sys
import os

BUILD_DIR = "/home/dev/workspaces/cdocx/build"
COMPARISON_DIR = "/home/dev/workspaces/cdocx/comparison"


def run(cmd, cwd=None, description=""):
    """Run a shell command and print status."""
    print(f"  {description or cmd} ...", end=" ", flush=True)
    result = subprocess.run(cmd, shell=True, cwd=cwd, capture_output=True, text=True)
    if result.returncode != 0:
        print("FAILED")
        print(result.stderr)
        return False
    print("OK")
    return True


def main():
    print("=" * 60)
    print("  cdocx Comparison Runner")
    print("=" * 60)

    # Clean stale cdocx artifacts from previous runs so analysis
    # only compares freshly-built documents.
    stale_patterns = [
        "cdocx_empty.docx",
        "cdocx_equivalent.docx",
        "09_text_formatting_output.docx",
        "document_builder_example.docx",
        "minimal_test.docx",
        "test_debug.docx",
        "test_hf.docx",
        "test_numbering.docx",
        "08_created_document.docx",
    ]
    for pattern in stale_patterns:
        path = os.path.join(BUILD_DIR, pattern)
        if os.path.exists(path):
            os.remove(path)
            print(f"  Cleaned stale artifact: {pattern}")

    # Step 1: Generate python-docx reference documents
    print("\n[1/4] Generating python-docx reference documents...")
    if not run(
        "python3 python_docx_reference.py",
        cwd=COMPARISON_DIR,
        description="python-docx references",
    ):
        return 1

    # Step 2: Build cdocx comparison binaries
    print("\n[2/4] Building cdocx comparison binaries...")
    compile_cmd = (
        f"g++ -std=c++17 -I/home/dev/workspaces/cdocx/include "
        f"-I{BUILD_DIR}/_deps/pugixml-src/src "
        f"-I{BUILD_DIR}/_deps/zip-src/src "
        f"{COMPARISON_DIR}/cdocx_empty.cpp "
        f"{BUILD_DIR}/libcdocx.a {BUILD_DIR}/_deps/pugixml-build/libpugixml.a "
        f"{BUILD_DIR}/_deps/zip-build/libzip.a -lz -lpthread "
        f"-o {BUILD_DIR}/cdocx_empty"
    )
    if not run(compile_cmd, description="cdocx_empty binary"):
        return 1

    compile_cmd = (
        f"g++ -std=c++17 -I/home/dev/workspaces/cdocx/include "
        f"-I{BUILD_DIR}/_deps/pugixml-src/src "
        f"-I{BUILD_DIR}/_deps/zip-src/src "
        f"{COMPARISON_DIR}/cdocx_equivalent.cpp "
        f"{BUILD_DIR}/libcdocx.a {BUILD_DIR}/_deps/pugixml-build/libpugixml.a "
        f"{BUILD_DIR}/_deps/zip-build/libzip.a -lz -lpthread "
        f"-o {BUILD_DIR}/cdocx_equivalent"
    )
    if not run(compile_cmd, description="cdocx_equivalent binary"):
        return 1

    # Step 3: Generate cdocx documents
    print("\n[3/4] Generating cdocx comparison documents...")
    if not run("./cdocx_empty", cwd=BUILD_DIR, description="cdocx_empty.docx"):
        return 1
    if not run("./cdocx_equivalent", cwd=BUILD_DIR, description="cdocx_equivalent.docx"):
        return 1

    # Step 4: Run analysis
    print("\n[4/4] Running structural analysis...")
    result = subprocess.run(
        f"python3 {COMPARISON_DIR}/compare_analysis.py",
        shell=True,
        cwd=BUILD_DIR,
        capture_output=True,
        text=True,
    )
    if result.returncode != 0:
        print("  Analysis FAILED")
        print(result.stderr)
        return 1
    print("  Analysis OK")
    print("\n" + result.stdout)

    # Summary
    print("=" * 60)
    print("  Comparison Complete")
    print("=" * 60)
    print("\nGenerated files:")
    print(f"  {BUILD_DIR}/cdocx_empty.docx")
    print(f"  {BUILD_DIR}/cdocx_equivalent.docx")
    print(f"  {BUILD_DIR}/python_docx_output/*.docx")
    return 0


if __name__ == "__main__":
    sys.exit(main())
