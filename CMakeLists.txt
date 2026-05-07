# ============================================================================
# CDocx - Cross-Platform CMake Build System
# ============================================================================
# C++17 library for creating, reading, and writing Microsoft Word DOCX files
# https://github.com/lonlng/CDocx
#
# Supported Platforms:
#   - Linux (GCC 7+, Clang 5+)
#   - Windows (MSVC 2017+, MinGW-w64)
#   - macOS (Xcode 10+)
#
# Usage:
#   mkdir build && cd build
#   cmake .. -G Ninja -DBUILD_EXAMPLES=ON -DBUILD_TESTING=ON
#   cmake --build . --target cdocx --parallel
#   ctest --output-on-failure
#
# Build Generators:
#   - Ninja (recommended): cmake .. -G Ninja
#   - Makefiles: cmake .. -G "Unix Makefiles"
#   - Visual Studio: cmake .. -G "Visual Studio 17 2022" -A x64
# ============================================================================

cmake_minimum_required(VERSION 3.14...3.28)

# ----------------------------------------------------------------------------
# Project Definition
# ----------------------------------------------------------------------------
project(cdocx
    VERSION 0.8.0
    DESCRIPTION "C++17 library for Microsoft Word DOCX files (Google C++ Style)"
    HOMEPAGE_URL "https://github.com/lonlng/cdocx"
    LANGUAGES CXX C
)

# ----------------------------------------------------------------------------
# CMake Module Path
# ----------------------------------------------------------------------------
list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

# ----------------------------------------------------------------------------
# Platform Detection
# ----------------------------------------------------------------------------
if(CMAKE_SYSTEM_NAME STREQUAL "Windows" OR CMAKE_SYSTEM_NAME STREQUAL "MSYS")
    set(CDOCX_PLATFORM_WINDOWS TRUE)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CDOCX_PLATFORM_LINUX TRUE)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(CDOCX_PLATFORM_MACOS TRUE)
endif()

# Detect compiler
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CDOCX_COMPILER_GCC TRUE)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang")
    set(CDOCX_COMPILER_CLANG TRUE)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CDOCX_COMPILER_MSVC TRUE)
endif()

# ----------------------------------------------------------------------------
# Build Options
# ----------------------------------------------------------------------------
option(BUILD_SHARED_LIBS "Build shared instead of static library" OFF)
option(BUILD_EXAMPLES "Build example programs" ON)
option(BUILD_TESTING "Build tests" ON)
option(BUILD_DOCS "Build documentation with Doxygen" OFF)
option(ENABLE_COVERAGE "Enable code coverage reporting (GCC/Clang only)" OFF)
option(ENABLE_WERROR "Treat warnings as errors" OFF)
option(USE_SYSTEM_GTEST "Use system installed Google Test instead of fetching" OFF)

# ----------------------------------------------------------------------------
# Language Standards
# ----------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Set default build type if not specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release' as none was specified")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# ----------------------------------------------------------------------------
# Compiler Warnings & Platform-specific Settings
# ----------------------------------------------------------------------------
if(CDOCX_COMPILER_MSVC)
    # MSVC specific options
    add_compile_options(
        /utf-8              # UTF-8 source and execution character set
        /W4                 # Warning level 4
        /permissive-        # Strict conformance mode
        /Zc:__cplusplus     # Enable updated __cplusplus macro
    )
    if(ENABLE_WERROR)
        add_compile_options(/WX)
    endif()
    # Disable specific warnings that are common in third-party code
    add_compile_options(
        /wd4267             # conversion from 'size_t' to 'type'
        /wd4244             # conversion from 'type1' to 'type2'
    )
elseif(CDOCX_COMPILER_GCC OR CDOCX_COMPILER_CLANG)
    # GCC/Clang options
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Wno-unused-parameter
        -Wno-sign-compare
    )
    
    # UTF-8 support on Linux
    if(CDOCX_PLATFORM_LINUX)
        add_compile_options(
            -finput-charset=utf-8
            -fexec-charset=utf-8
        )
    endif()
    
    if(ENABLE_WERROR)
        add_compile_options(-Werror)
    endif()
    
    # Coverage support
    if(ENABLE_COVERAGE AND CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-fprofile-arcs -ftest-coverage)
        add_link_options(-fprofile-arcs -ftest-coverage)
    endif()
endif()

# ----------------------------------------------------------------------------
# Position Independent Code (required for shared libraries)
# ----------------------------------------------------------------------------
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# ----------------------------------------------------------------------------
# MSVC Runtime Library Settings (Windows only)
# ----------------------------------------------------------------------------
# Set globally to ensure all targets (cdocx, thirdparty libs, examples, tests)
# use the same runtime library to avoid LNK2038 errors.
# Default: Static runtime (/MT, /MTd). Use BUILD_SHARED_LIBS=ON for dynamic.
# ----------------------------------------------------------------------------
if(MSVC AND NOT DEFINED CMAKE_MSVC_RUNTIME_LIBRARY)
    set(CMAKE_MSVC_RUNTIME_LIBRARY 
        "MultiThreaded$<$<CONFIG:Debug>:Debug>$<$<BOOL:${BUILD_SHARED_LIBS}>:DLL>")
    message(STATUS "MSVC Runtime Library: ${CMAKE_MSVC_RUNTIME_LIBRARY}")
endif()

# Also set as cache variable so FetchContent dependencies can see it
if(MSVC)
    # Ensure FetchContent dependencies (pugixml, zip) inherit the same runtime.
    # CMAKE_MSVC_RUNTIME_LIBRARY (CMake 3.15+) controls both C and C++ targets.
    # Do NOT set CMAKE_C_FLAGS_RELEASE/DEBUG here — hardcoding /MT would
    # override the generator expression for C libraries, causing LNK2038
    # runtime mismatch when BUILD_SHARED_LIBS=ON (/MD).
    set(CMAKE_MSVC_RUNTIME_LIBRARY "${CMAKE_MSVC_RUNTIME_LIBRARY}" CACHE STRING "MSVC Runtime Library" FORCE)
endif()

# ----------------------------------------------------------------------------
# Source Files (Auto-collecting)
# ----------------------------------------------------------------------------
file(GLOB_RECURSE CDOCX_SOURCES CONFIGURE_DEPENDS 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)
file(GLOB_RECURSE CDOCX_PUBLIC_HEADERS CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

# ----------------------------------------------------------------------------
# Library Target
# ----------------------------------------------------------------------------
# Windows: auto-export all symbols from DLL so import library (.lib) is generated
if(WIN32 AND BUILD_SHARED_LIBS)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

add_library(cdocx ${CDOCX_SOURCES})
add_library(cdocx::cdocx ALIAS cdocx)

# Rename static library output to avoid collision with shared import library
if(NOT BUILD_SHARED_LIBS)
    set_target_properties(cdocx PROPERTIES ARCHIVE_OUTPUT_NAME "cdocx_static")
endif()

target_include_directories(cdocx
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/detail
)

# Export macros for shared library
target_compile_definitions(cdocx
    PUBLIC
        $<$<BOOL:${BUILD_SHARED_LIBS}>:CDOCX_SHARED>
    PRIVATE
        $<$<BOOL:${BUILD_SHARED_LIBS}>:CDOCX_EXPORTS>
)

# MSVC runtime library settings (must match examples and tests)
if(MSVC)
    set_property(TARGET cdocx PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>$<$<BOOL:${BUILD_SHARED_LIBS}>:DLL>")
endif()

# ----------------------------------------------------------------------------
# Dependencies - FetchContent
# ----------------------------------------------------------------------------
include(FetchContent)

# Set options to speed up FetchContent
set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

# ----------------------------------------------------------------------------
# pugixml - XML parsing library
# ----------------------------------------------------------------------------
FetchContent_Declare(
    pugixml
    GIT_REPOSITORY https://gitee.com/lonlng/pugixml.git
    GIT_TAG v1.15
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    GIT_CONFIG "http.lowSpeedLimit=1000;http.lowSpeedTime=60"
)

# ----------------------------------------------------------------------------
# zip - ZIP archive handling library
# ----------------------------------------------------------------------------
FetchContent_Declare(
    zip
    GIT_REPOSITORY https://gitee.com/lonlng/zip.git
    GIT_TAG v0.3.6
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    GIT_CONFIG "http.lowSpeedLimit=1000;http.lowSpeedTime=60"
)

# Make dependencies available
FetchContent_MakeAvailable(pugixml zip)

# Suppress GCC warnings in third-party C library (zip)
# -Wstringop-truncation was introduced in GCC 8 and triggered by zip.c
if(CMAKE_C_COMPILER_ID STREQUAL "GNU" AND CMAKE_C_COMPILER_VERSION VERSION_GREATER_EQUAL "8")
    if(TARGET zip)
        target_compile_options(zip PRIVATE -Wno-stringop-truncation)
    endif()
endif()

target_link_libraries(cdocx 
    PUBLIC pugixml
    PUBLIC zip::zip
)

# Platform-specific libraries
if(WIN32)
    target_link_libraries(cdocx PRIVATE bcrypt)
    # Windows-specific defines
    target_compile_definitions(cdocx PRIVATE
        NOMINMAX            # Prevent min/max macro conflicts
        WIN32_LEAN_AND_MEAN # Reduce Windows.h bloat
        _CRT_SECURE_NO_WARNINGS
    )
endif()

# ----------------------------------------------------------------------------
# Examples
# ----------------------------------------------------------------------------
if(BUILD_EXAMPLES)
    message(STATUS "")
    message(STATUS "[Examples] ENABLED")
    add_subdirectory(examples)
endif()

# ----------------------------------------------------------------------------
# Testing
# ----------------------------------------------------------------------------
if(BUILD_TESTING AND CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message(STATUS "")
    message(STATUS "[Testing] ENABLED")
    
    # Google Test integration
    if(USE_SYSTEM_GTEST)
        find_package(GTest QUIET)
        if(GTest_FOUND)
            message(STATUS "Using system Google Test")
        else()
            message(WARNING "System Google Test not found, falling back to FetchContent")
            set(USE_SYSTEM_GTEST OFF)
        endif()
    endif()
    
    if(NOT USE_SYSTEM_GTEST)
        include(FetchContent)
        
        # Set options to speed up FetchContent
        set(FETCHCONTENT_QUIET OFF)
        set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
        
        FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://gitee.com/lonlng/googletest.git
            GIT_TAG v1.17.0
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE
            GIT_CONFIG "http.lowSpeedLimit=1000;http.lowSpeedTime=60"
        )
        
        # For Windows: Prevent overriding the parent project's compiler/linker settings
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        
        # Make available with timeout handling
        FetchContent_MakeAvailable(googletest)
    endif()
    
    enable_testing()
    add_subdirectory(test)
elseif(BUILD_TESTING)
    message(STATUS "[Testing] DISABLED (not building as main project)")
endif()

# ----------------------------------------------------------------------------
# Documentation
# ----------------------------------------------------------------------------
if(BUILD_DOCS)
    find_package(Doxygen OPTIONAL_COMPONENTS dot)
    if(DOXYGEN_FOUND)
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} COPYONLY)
        
        add_custom_target(doxygen
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM
        )
    else()
        message(WARNING "Doxygen not found, documentation will not be built")
    endif()
endif()

# ----------------------------------------------------------------------------
# Installation
# ----------------------------------------------------------------------------
include(GNUInstallDirs)

install(TARGETS cdocx
    EXPORT cdocxConfig
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT cdocx
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT cdocx
    # Place DLL next to import lib on Windows (consistent with vcpkg layout)
    RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT cdocx
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    COMPONENT cdocx
    FILES_MATCHING PATTERN "*.h"
)

install(EXPORT cdocxConfig
    FILE cdocx-config.cmake
    NAMESPACE cdocx::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cdocx COMPONENT cdocx
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/cdocx-config-version.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/cdocx-config-version.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cdocx COMPONENT cdocx
)

# ----------------------------------------------------------------------------
# Custom Targets
# ----------------------------------------------------------------------------
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean
    COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_BINARY_DIR}/test"
    COMMENT "Cleaning all build artifacts"
)

# ----------------------------------------------------------------------------
# Code Quality Tools - Clang-Format & Clang-Tidy
# ----------------------------------------------------------------------------

# ---- Clang-Format ---------------------------------------------------------
find_program(CLANG_FORMAT clang-format)
if(CLANG_FORMAT)
    file(GLOB_RECURSE FORMAT_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    )
    add_custom_target(format
        COMMAND ${CLANG_FORMAT} -i ${FORMAT_SOURCES}
        COMMENT "Formatting source code with clang-format"
    )
    add_custom_target(format-check
        COMMAND ${CLANG_FORMAT} --dry-run --Werror ${FORMAT_SOURCES}
        COMMENT "Checking code formatting"
    )
    message(STATUS "[Tools] clang-format found: ${CLANG_FORMAT}")
else()
    message(STATUS "[Tools] clang-format not found")
endif()

# ---- Clang-Tidy -------------------------------------------------------------
find_program(CLANG_TIDY clang-tidy)
if(CLANG_TIDY)
    # Collect source files for analysis
    file(GLOB_RECURSE TIDY_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    )
    
    # Get compile commands directory
    set(TIDY_COMPILE_COMMANDS_DIR ${CMAKE_BINARY_DIR})
    
    # Create tidy target (analysis only)
    add_custom_target(tidy
        COMMAND ${CLANG_TIDY}
            -p ${TIDY_COMPILE_COMMANDS_DIR}
            --config-file=${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy
            ${TIDY_SOURCES}
        COMMENT "Running clang-tidy static analysis"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
    
    # Create tidy-fix target (auto-fix issues)
    add_custom_target(tidy-fix
        COMMAND ${CLANG_TIDY}
            -p ${TIDY_COMPILE_COMMANDS_DIR}
            --config-file=${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy
            --fix
            --fix-errors
            ${TIDY_SOURCES}
        COMMENT "Running clang-tidy with auto-fix"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
    
    # Optional: Enable tidy checks during compilation (for CI)
    option(ENABLE_CLANG_TIDY_DURING_BUILD "Run clang-tidy during compilation" OFF)
    if(ENABLE_CLANG_TIDY_DURING_BUILD)
        set(CMAKE_CXX_CLANG_TIDY 
            ${CLANG_TIDY}
            -p ${TIDY_COMPILE_COMMANDS_DIR}
            --config-file=${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy
        )
    endif()
    
    message(STATUS "[Tools] clang-tidy found: ${CLANG_TIDY}")
    message(STATUS "[Tools] clang-tidy targets: tidy, tidy-fix")
    if(ENABLE_CLANG_TIDY_DURING_BUILD)
        message(STATUS "[Tools] clang-tidy during build: ENABLED")
    endif()
else()
    message(STATUS "[Tools] clang-tidy not found")
endif()

# ---- Code Quality Summary Target --------------------------------------------
if(CLANG_FORMAT OR CLANG_TIDY)
    add_custom_target(code-quality
        COMMENT "Running all code quality checks"
    )
    if(CLANG_FORMAT)
        add_dependencies(code-quality format-check)
    endif()
    if(CLANG_TIDY)
        add_dependencies(code-quality tidy)
    endif()
endif()

# ----------------------------------------------------------------------------
# Build Summary
# ----------------------------------------------------------------------------
message(STATUS "")
message(STATUS "╔════════════════════════════════════════════════════════════╗")
message(STATUS "║              CDocx Build Configuration                     ║")
message(STATUS "╠════════════════════════════════════════════════════════════╣")
message(STATUS "║ Version:          ${PROJECT_VERSION}                                     ║")
message(STATUS "║ Platform:         ${CMAKE_SYSTEM_NAME}                                 ║")
message(STATUS "║ Compiler:         ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}           ║")
message(STATUS "║ C++ Standard:     C++${CMAKE_CXX_STANDARD}                                ║")
message(STATUS "║ Build Type:       ${CMAKE_BUILD_TYPE}                              ║")
message(STATUS "║ Shared Library:   ${BUILD_SHARED_LIBS}                                  ║")
message(STATUS "║ Examples:         ${BUILD_EXAMPLES}                                   ║")
message(STATUS "║ Testing:          ${BUILD_TESTING}                                    ║")
message(STATUS "║ Documentation:    ${BUILD_DOCS}                                   ║")
message(STATUS "╚════════════════════════════════════════════════════════════╝")
message(STATUS "")
