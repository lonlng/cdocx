---
name: VS2022 Debug CMake Command
description: 本地 Windows 下使用 Qt 自带的 CMake 和 VS2022 生成器配置 CDocx Debug 构建的命令
type: project
originSessionId: d614572b-0016-421b-8a03-e2813abfdb1b
---
本地 Windows 下配置 CDocx Debug 构建的 CMake 命令：

```bash
D:/Qt/Tools/CMake_64/bin/cmake.EXE -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE --no-warn-unused-cli -S D:/workspace/code/cdocx -B d:/workspace/code/cdocx/build -G "Visual Studio 17 2022" -T host=x64 -A x64
```

**验证结果**：配置成功（2026/04/15）。生成 Visual Studio 2022 工程文件到 `d:/workspace/code/cdocx/build`。

**注意**：原代码中 `test/CMakeLists.txt` 的 `add_test_suite` 宏存在路径 bug，调用 `add_cdocx_test` 时未传递子目录路径，导致 `10_dom_sync_tests.cpp` 无法找到。修复方式：将 `${test_cpp}` 改为 `${test_dir}/${test_cpp}` 传入 `add_cdocx_test`。
