# GitHub 自动发布库文件 - 设计文档

**日期**: 2026-05-06
**主题**: cdocx 项目 GitHub Actions 自动构建发布库文件

---

## 需求概述

为 cdocx 项目设置 GitHub Actions 工作流，在推送版本标签时自动构建 Windows 和 Linux 平台的动态库、静态库以及 include 头文件，并作为 GitHub Release 附件发布。

## 触发条件

- **触发方式**: 推送 `v*.*.*` 格式的 git tag（如 `v0.9.0`）
- **行为**: 自动构建多平台库文件，创建 GitHub Release，上传产物
- **Release 标题**: 自动使用 tag 名称
- **Release 描述**: 自动生成产物清单

## 构建矩阵

共 4 个并行构建作业：

| 作业 | Runner | 编译器 | 配置 | 库类型 |
|------|--------|--------|------|--------|
| windows-release | windows-2022 | MSVC 2022 x64 | Release | static + shared |
| windows-debug | windows-2022 | MSVC 2022 x64 | Debug | static + shared |
| linux-release | ubuntu-latest | GCC x64 | Release | static + shared |
| linux-debug | ubuntu-latest | GCC x64 | Debug | static + shared |

### Windows 配置

- 静态库使用 `/MT`（由项目默认 CMake 配置自动处理）
- 动态库使用 `/MD`（由 `BUILD_SHARED_LIBS=ON` 自动切换）
- 动态库同时产出 `.lib`（导入库）和 `.dll`

### Linux 配置

- 静态库产出 `.a`
- 动态库产出 `.so`
- 静态库和动态库独立构建，不冲突

## 产物结构

每个包包含 `include/`（头文件）和 `lib/`（库文件）两个目录。

### Windows 产物结构

```
cdocx-0.8.0-windows-msvc-x64-{config}.zip
  ├─ include/
  │   ├─ cdocx.h
  │   └─ cdocx/*.h
  └─ lib/
      ├─ cdocx_static.lib      # 静态库 (/MT)
      ├─ cdocx.lib             # 动态库导入库 (/MD)
      └─ cdocx.dll             # 动态库
```

### Linux 产物结构

```
cdocx-0.8.0-linux-gcc-x64-{config}.tar.gz
  ├─ include/
  │   ├─ cdocx.h
  │   └─ cdocx/*.h
  └─ lib/
      ├─ libcdocx.a            # 静态库
      └─ libcdocx.so           # 动态库
```

## 技术实现

### 工作流结构

采用自定义打包方案：在 GitHub Actions 中分别构建静态库和动态库，用 `cmake --install --prefix` 安装到临时目录，然后手动 `zip`/`tar.gz` 打包。

### 关键步骤

1. **检出代码**: `actions/checkout@v4`
2. **安装依赖**: CMake、Ninja（Linux）
3. **构建静态库**: `cmake -B build_static -DBUILD_SHARED_LIBS=OFF`
4. **安装静态库**: `cmake --install build_static --prefix staging/lib`
5. **构建动态库**: `cmake -B build_shared -DBUILD_SHARED_LIBS=ON`
6. **安装动态库**: `cmake --install build_shared --prefix staging/lib`
7. **复制头文件**: 复制 `include/` 到 staging
8. **打包**: `zip`（Windows）或 `tar czf`（Linux）
9. **上传产物**: 使用 `actions/upload-artifact@v4` 暂存
10. **创建 Release**: 使用 `softprops/action-gh-release@v1` 从所有作业收集产物并发布

### 并行策略

4 个作业完全独立并行执行，无依赖关系。最终由 Release 作业（依赖全部 4 个构建作业）汇总上传。

### 版本号提取

从 git tag 中提取版本号：
- 输入: `refs/tags/v0.9.0`
- 输出: `0.9.0`

用于产物文件名和 Release 描述。

## 需要修改的文件

1. **新建** `.github/workflows/release.yml` — 完整的发布工作流
2. **可选修改** `CMakeLists.txt` — 确保安装目标正确（已有 `install(TARGETS...)` 和 `install(FILES...)` 配置，基本满足）

## 现有基础设施复用

- 项目已有 CMake 构建系统和安装目标
- 已有 `BUILD_SHARED_LIBS` 选项控制动态/静态构建
- 已有 `install(TARGETS cdocx...)` 和 `install(FILES ${CDOCX_PUBLIC_HEADERS}...)`
- 已有 `.github/workflows/cmake.yml` 作为参考

## 产物文件名格式

```
cdocx-{version}-{platform}-{compiler}-{arch}-{config}.{ext}

示例:
- cdocx-0.9.0-windows-msvc-x64-release.zip
- cdocx-0.9.0-windows-msvc-x64-debug.zip
- cdocx-0.9.0-linux-gcc-x64-release.tar.gz
- cdocx-0.9.0-linux-gcc-x64-debug.tar.gz
```
