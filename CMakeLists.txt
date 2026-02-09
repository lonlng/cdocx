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
option(BUILD_DOCS "Build documentation with Doxygen" OFF)

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
# Source and Header Files (Refactored Structure)
# ============================================================================

# Main public header (includes all modules)
set(CDOCX_PUBLIC_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cdocx.h
)

# Modular headers in cdocx/ directory
set(CDOCX_MODULE_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cdocx/fwd.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cdocx/constants.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cdocx/iterator.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cdocx/base.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cdocx/document.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cdocx/template.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cdocx/inserter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cdocx/advanced.h
)

# Private implementation headers
set(CDOCX_PRIVATE_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/detail/impl.h
)

# Source files (refactored structure)
set(CDOCX_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/base_content.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/document.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/template.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/inserter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tree.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/impl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/advanced.cpp
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

# Find Doxygen for documentation
if(BUILD_DOCS)
    find_package(Doxygen)
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

# Install main header
install(
    FILES ${CDOCX_PUBLIC_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install modular headers
install(
    FILES ${CDOCX_MODULE_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cdocx
)

# Install private headers (optional, for advanced users)
install(
    FILES ${CDOCX_PRIVATE_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cdocx/detail
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
message(STATUS "Build Documentation: ${BUILD_DOCS}")
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
if(BUILD_DOCS AND DOXYGEN_FOUND)
    add_custom_target(docs
        DEPENDS doxygen
        COMMENT "Build documentation with Doxygen"
    )
else()
    add_custom_target(docs
        COMMENT "Documentation not built (Doxygen not available or disabled)"
    )
endif()

# Add custom target for cleaning build artifacts
add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean
    COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_BINARY_DIR}/test/test_data"
    COMMENT "Cleaning all build artifacts and test data"
)

# Add format target (requires clang-format)
find_program(CLANG_FORMAT clang-format)
if(CLANG_FORMAT)
    file(GLOB_RECURSE ALL_SOURCE_FILES 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    )
    add_custom_target(format
        COMMAND ${CLANG_FORMAT} -i ${ALL_SOURCE_FILES}
        COMMENT "Formatting source code with clang-format"
    )
endif()
