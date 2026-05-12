cmake_minimum_required(VERSION 3.14)
project(cdocx_install_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(cdocx REQUIRED)

add_executable(install_test src/main.cpp)
target_link_libraries(install_test PRIVATE cdocx::cdocx)
