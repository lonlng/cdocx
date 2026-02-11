# ============================================================================
# CDocx - Modern CMake Build System
# ============================================================================
# C++17 library for creating, reading, and writing Microsoft Word DOCX files
# https://github.com/lonlng/CDocx
#
# Usage:
#   mkdir build && cd build
#   cmake .. -DBUILD_EXAMPLES=ON -DBUILD_TESTING=ON
#   cmake --build . --target cdocx
#   ctest -C Debug
# ============================================================================

cmake_minimum_required(VERSION 3.14...3.28)

# ----------------------------------------------------------------------------
# Project Definition
# ----------------------------------------------------------------------------
project(cdocx
    VERSION 0.4.0
    DESCRIPTION "C++ library for creating, reading, and writing Microsoft Word DOCX files"
    HOMEPAGE_URL "https://github.com/lonlng/cdocx"
    LANGUAGES CXX C
)

# ----------------------------------------------------------------------------
# CMake Module Path
# ----------------------------------------------------------------------------
list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

# ----------------------------------------------------------------------------
# Build Options
# ----------------------------------------------------------------------------
option(BUILD_SHARED_LIBS "Build shared instead of static library" OFF)
option(BUILD_EXAMPLES "Build example programs" ON)
option(BUILD_TESTING "Build tests" ON)
option(BUILD_DOCS "Build documentation with Doxygen" OFF)
option(ENABLE_COVERAGE "Enable code coverage reporting" OFF)
option(ENABLE_WERROR "Treat warnings as errors" OFF)

# ----------------------------------------------------------------------------
# Language Standards
# ----------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# ----------------------------------------------------------------------------
# Compiler Warnings & Encoding
# ----------------------------------------------------------------------------
if(MSVC)
    add_compile_options(/utf-8 /W4)
    if(ENABLE_WERROR)
        add_compile_options(/WX)
    endif()
else()
    add_compile_options(
        -finput-charset=utf-8
        -fexec-charset=utf-8
        -Wall -Wextra -Wpedantic
    )
    if(ENABLE_WERROR)
        add_compile_options(-Werror)
    endif()
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
add_library(cdocx ${CDOCX_SOURCES})
add_library(cdocx::cdocx ALIAS cdocx)

target_include_directories(cdocx
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/detail
)

target_compile_definitions(cdocx
    PUBLIC
        $<$<BOOL:${BUILD_SHARED_LIBS}>:CDOCX_SHARED>
)

# ----------------------------------------------------------------------------
# Dependencies
# ----------------------------------------------------------------------------
add_subdirectory(thirdparty/pugixml)
add_subdirectory(thirdparty/zip)

target_link_libraries(cdocx 
    PUBLIC pugixml
    PRIVATE zip::zip
)

if(WIN32)
    target_link_libraries(cdocx PRIVATE bcrypt)
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

install(TARGETS cdocx pugixml
    EXPORT cdocxConfig
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES ${CDOCX_PUBLIC_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cdocx
)

install(EXPORT cdocxConfig
    FILE cdocx-config.cmake
    NAMESPACE cdocx::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cdocx
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/cdocx-config-version.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/cdocx-config-version.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cdocx
)

# ----------------------------------------------------------------------------
# Custom Targets
# ----------------------------------------------------------------------------
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean
    COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_BINARY_DIR}/test"
    COMMENT "Cleaning all build artifacts"
)

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
endif()

# ----------------------------------------------------------------------------
# Build Summary
# ----------------------------------------------------------------------------
message(STATUS "")
message(STATUS "╔════════════════════════════════════════════════════════════╗")
message(STATUS "║              CDocx Build Configuration                     ║")
message(STATUS "╠════════════════════════════════════════════════════════════╣")
message(STATUS "║ Version:          ${PROJECT_VERSION}                       ║")
message(STATUS "║ C++ Standard:     C++${CMAKE_CXX_STANDARD}                 ║")
message(STATUS "║ Build Type:       ${CMAKE_BUILD_TYPE}                      ║")
message(STATUS "║ Shared Library:   ${BUILD_SHARED_LIBS}                     ║")
message(STATUS "║ Examples:         ${BUILD_EXAMPLES}                        ║")
message(STATUS "║ Testing:          ${BUILD_TESTING}                         ║")
message(STATUS "║ Documentation:    ${BUILD_DOCS}                            ║")
message(STATUS "╚════════════════════════════════════════════════════════════╝")
message(STATUS "")
