cmake_minimum_required(VERSION 3.10)

# ============================================================================
# Project Definition
# ============================================================================

project(cdocx
    VERSION 0.2.0
    DESCRIPTION "C++ library for creating, reading, and writing Microsoft Word DOCX files"
    HOMEPAGE_URL "https://github.com/amiremohamadi/CDocx"
    LANGUAGES CXX C
)

# ============================================================================
# Options and Configuration
# ============================================================================

option(BUILD_SHARED_LIBS "Build shared instead of static library" OFF)
option(BUILD_EXAMPLES "Build example programs" ON)
option(BUILD_TESTING "Build tests" ON)
option(ENABLE_ADVANCED_FEATURES "Enable advanced template and insertion features" ON)

# C++17 Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# C99 Standard for C files (zip library)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# ============================================================================
# UTF-8 Encoding (important for international characters)
# ============================================================================

if(MSVC)
    add_compile_options(/utf-8)
else()
    add_compile_options(-finput-charset=utf-8 -fexec-charset=utf-8)
endif()

# ============================================================================
# Source and Header Files
# ============================================================================

set(CDOCX_PUBLIC_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cdocx.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/constants.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cdocxIterator.h
)

set(CDOCX_PRIVATE_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/detail/cdocx_impl.h
)

set(CDOCX_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cdocx_document.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cdocx_tree.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cdocx_content.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cdocx_template.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cdocx_impl.cpp
)

set(CDOCX_THIRD_PARTY_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/zip/src/zip.h
)

set(CDOCX_THIRD_PARTY_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/zip/src/zip.c
)

# ============================================================================
# Include Directories
# ============================================================================

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/detail
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/zip/src
)

# ============================================================================
# Third-Party Dependencies
# ============================================================================

# pugixml (Git submodule)
add_subdirectory(thirdparty/pugixml)

# ============================================================================
# CDocx Library Target
# ============================================================================

if(BUILD_SHARED_LIBS)
    add_library(cdocx SHARED ${CDOCX_SOURCES} ${CDOCX_THIRD_PARTY_SOURCES})
    target_compile_definitions(cdocx PUBLIC CDOCX_SHARED)
else()
    add_library(cdocx STATIC ${CDOCX_SOURCES} ${CDOCX_THIRD_PARTY_SOURCES})
endif()

add_library(cdocx::cdocx ALIAS cdocx)

# Link with pugixml (PUBLIC so include directories propagate to dependents)
target_link_libraries(cdocx PUBLIC pugixml)

# Set include directories for users of the library
target_include_directories(cdocx PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# ============================================================================
# Platform-Specific Configurations
# ============================================================================

if(WIN32)
    target_link_libraries(cdocx PRIVATE bcrypt)  # For zip library on Windows
endif()

# ============================================================================
# Build Examples
# ============================================================================

if(BUILD_EXAMPLES)
    message(STATUS "")
    message(STATUS "Example programs: ENABLED")
    add_subdirectory(examples)
endif()

# ============================================================================
# Build Tests
# ============================================================================

if(BUILD_TESTING AND CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message(STATUS "")
    message(STATUS "Testing: ENABLED")
    enable_testing()
    add_subdirectory(test)
elseif(BUILD_TESTING)
    message(STATUS "")
    message(STATUS "Testing: DISABLED (not building as main project)")
endif()

# ============================================================================
# Installation Rules
# ============================================================================

include(GNUInstallDirs)

# Install library
target_include_directories(cdocx PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(
    TARGETS cdocx pugixml
    EXPORT cdocxConfig
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install headers
install(
    FILES ${CDOCX_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cdocx
)

# Install third-party headers
install(
    FILES ${CDOCX_THIRD_PARTY_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cdocx/thirdparty
)

# Install CMake config
install(
    EXPORT cdocxConfig
    FILE cdocx-config.cmake
    NAMESPACE cdocx::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cdocx
)

# ============================================================================
# Package Configuration
# ============================================================================

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/cdocx-config-version.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/cdocx-config-version.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cdocx
)

# ============================================================================
# Summary
# ============================================================================

message(STATUS "")
message(STATUS "========================================")
message(STATUS "CDocx Build Configuration")
message(STATUS "========================================")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "C++ Standard: C++${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Shared Library: ${BUILD_SHARED_LIBS}")
message(STATUS "Build Examples: ${BUILD_EXAMPLES}")
message(STATUS "Build Tests: ${BUILD_TESTING}")
message(STATUS "Advanced Features: ${ENABLE_ADVANCED_FEATURES}")
message(STATUS "========================================")
message(STATUS "")

# ============================================================================
# Custom Targets
# ============================================================================

# Add custom target to run all examples
if(BUILD_EXAMPLES)
    add_custom_target(run_examples
        COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIG> --test-dir ${CMAKE_BINARY_DIR}/examples
        COMMENT "Running all CDocx examples"
    )
    add_dependencies(run_examples cdocx)
endif()

# Add custom target for documentation
add_custom_target(docs
    COMMENT "Build documentation (placeholder - add Doxygen or similar here)"
)

# Add custom target for cleaning build artifacts
add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean
    COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_BINARY_DIR}/test/test_data"
    COMMENT "Cleaning all build artifacts and test data"
)
