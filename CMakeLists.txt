cmake_minimum_required(VERSION 3.0)

project(cdocx VERSION 0.2)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	include(CTest)
endif()

option(BUILD_SHARED_LIBS "Build shared instead of static library" OFF)
option(BUILD_SAMPLES "Build provided samples" ON)

# Fix issues when building with clang 12, next version of clang
# else we might encounter errors making the library 
# not being able to be compiled

set(CMAKE_CXX_STANDARD 17)

# Set UTF-8 encoding for source files
# This is important for proper handling of Unicode characters in C++ code
if(MSVC)
    # For Visual Studio: Set source and execution charset to UTF-8
    add_compile_options(/utf-8)
else()
    # For GCC and Clang: Set input and execution charset to UTF-8
    add_compile_options(-finput-charset=utf-8 -fexec-charset=utf-8)
endif()


set(HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/cdocx.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/include/constants.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/include/cdocxIterator.h")
set(SOURCES src/cdocx.cpp)

set(THIRD_PARTY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/zip/zip.h")
set(THIRD_PARTY_SRC "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/zip/zip.c")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include"
                    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/zip")

# Add pugixml subdirectory
add_subdirectory(thirdparty/pugixml)

if(BUILD_SHARED_LIBS)
    add_library(cdocx SHARED ${SOURCES} ${THIRD_PARTY_SRC})
else()
    add_library(cdocx STATIC ${SOURCES} ${THIRD_PARTY_SRC})
endif()

add_library(cdocx::cdocx ALIAS cdocx)

# Link with pugixml and add its include directories
target_link_libraries(cdocx PRIVATE pugixml)
target_include_directories(cdocx PUBLIC $<TARGET_PROPERTY:pugixml,INTERFACE_INCLUDE_DIRECTORIES>)

# Also add pugixml include directory for compatibility
target_include_directories(cdocx PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/pugixml/src>)

target_include_directories(cdocx PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)

mark_as_advanced(CLEAR CMAKE_INSTALL_LIBDIR CMAKE_INSTALL_INCLUDEDIR)

if (BUILD_SAMPLES)
	# Sample executable - Basic document reading example
	# set(SAMPLE1_SOURCES samples/sample1.cpp)
	# add_executable(cdocx_sample1 ${SAMPLE1_SOURCES})
	# target_link_libraries(cdocx_sample1 cdocx)
	# # Set working directory to samples folder for Visual Studio debugger
	# set_target_properties(cdocx_sample1 PROPERTIES
	# 	VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/samples"
	# )

	# Sample executable - Document creation example
	# set(SAMPLE2_SOURCES samples/sample2.cpp)
	# add_executable(cdocx_sample2 ${SAMPLE2_SOURCES})
	# target_link_libraries(cdocx_sample2 cdocx)
	# # Set working directory to samples folder for Visual Studio debugger
	# set_target_properties(cdocx_sample2 PROPERTIES
	# 	VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/samples"
	# )

	# Template sample - Basic template replacement
	set(SAMPLE_TEMPLATE_SOURCES samples/sample_template.cpp)
	add_executable(cdocx_template_sample ${SAMPLE_TEMPLATE_SOURCES})
	target_link_libraries(cdocx_template_sample cdocx)
	# Set working directory to samples folder for Visual Studio debugger
	set_target_properties(cdocx_template_sample PROPERTIES
		VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/samples"
		RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/samples"
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/samples"
	)

	# Advanced template sample - Multiple templates and patterns
	# set(SAMPLE_ADV_TEMPLATE_SOURCES samples/advanced_template.cpp)
	# add_executable(cdocx_advanced_template ${SAMPLE_ADV_TEMPLATE_SOURCES})
	# target_link_libraries(cdocx_advanced_template cdocx)
	# # Set working directory to samples folder for Visual Studio debugger
	# set_target_properties(cdocx_advanced_template PROPERTIES
	# 	VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/samples"
	# )

	# Employee report template sample - Comprehensive template demonstration
	# set(SAMPLE_EMP_REPORT_SOURCES samples/employee_report_template.cpp)
	# add_executable(cdocx_employee_report ${SAMPLE_EMP_REPORT_SOURCES})
	# target_link_libraries(cdocx_employee_report cdocx)
	# # Set working directory to samples folder for Visual Studio debugger
	# set_target_properties(cdocx_employee_report PROPERTIES
	# 	VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/samples"
	# )

        # Copy sample document files to build directory for command-line execution
        # This ensures samples work both in Visual Studio (with working dir set)
        # and from command line (when run from build directory)
        file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/samples/my_test.docx
            DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
        file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/samples/template_sample.docx
            DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
        # file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/samples/template_sample2.docx
        #     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()

include(GNUInstallDirs)
install(
    TARGETS cdocx
    EXPORT cdocxConfig
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}${INSTALL_SUFFIX}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}${INSTALL_SUFFIX}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
install(EXPORT cdocxConfig NAMESPACE cdocx:: DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cdocx)
install(FILES ${HEADERS} ${THIRD_PARTY_HEADERS} DESTINATION include/cdocx)


if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
	enable_testing()
	add_subdirectory(test)
endif()
