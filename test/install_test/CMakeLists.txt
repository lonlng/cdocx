cmake_minimum_required(VERSION 3.14)
project(cdocx_install_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Match cdocx runtime library setting (/MT for static builds)
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    # Also force /MT via compiler flags as a fallback
    add_compile_options($<$<CONFIG:Debug>:/MTd>$<$<CONFIG:Release>:/MT>)
endif()

find_package(cdocx REQUIRED)

add_executable(install_test src/main.cpp)
target_link_libraries(install_test PRIVATE cdocx::cdocx)
