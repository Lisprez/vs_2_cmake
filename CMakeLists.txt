cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(my_project_name CXX)

set_property(GLOBAL PROPERTY USE_FOLDER ON)

set(SOURCE_FILE_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_FILE_DIR    ${CMAKE_CURRENT_SOURCE_DIR}/inc)

set(CMAKE_BINARY_DIR    ${CMAKE_SOURCE_DIR}/build/output)
set(CMAKE_MODULE_PATH   ${CMAKE_SOURCE_DIR}/CMake/modules)

add_definitions(-std=c++14)

include_directories(${INCLUDE_FILE_DIR})

set(CURRENT_SOURCE_FILES 
    ${SOURCE_FILE_DIR}/main.cpp
    ${SOURCE_FILE_DIR}/print.cpp)

set(CURRENT_HEADER_FILES
    ${INCLUDE_FILE_DIR}/print.h)

macro(GroupSource current_source_dir)
    file(GLOB children RELATIVE ${current_source_dir} ${current_source_dir}/*)
    foreach(child ${children})
        if (IS_DIRECTORY ${current_source_dir}/${child})
            GroupSource(${current_source_dir}/${child})
        else()
            get_filename_component(base ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
            string(REPLACE ${base} "" groupname ${current_source_dir})
            string(REPLACE "/" "\\" new_groupname ${groupname})
            source_group(${new_groupname} FILES ${current_source_dir}/${child})
        endif()
    endforeach()
endmacro()

GroupSource(${SOURCE_FILE_DIR})
GroupSource(${INCLUDE_FILE_DIR})

add_executable(${PROJECT_NAME} 
    ${CURRENT_SOURCE_FILES} 
    ${CURRENT_HEADER_FILES})

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
