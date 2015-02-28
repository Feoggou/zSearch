cmake_minimum_required (VERSION 3.1)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "module path= ${CMAKE_MODULE_PATH}")

include(Macros)

option(PROJ_LIB_TYPES "Use zSearch and XLib as static libs." "STATIC")
if (NOT PROJ_LIB_TYPES)
    set(PROJ_LIB_TYPES "STATIC")
endif()
message(STATUS "PROJ_LIB_TYPES=${PROJ_LIB_TYPES}")

enable_testing()

project(Zen)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY    ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY    ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY    ${CMAKE_BINARY_DIR}/bin)

if (MSVC)
    set(CFLAG CMAKE_CXX_FLAGS_DEBUG)
    string(REPLACE "/MD" "/MT" ${CFLAG} "${${CFLAG}}")
    message(STATUS "link flags: ${CMAKE_CXX_FLAGS_DEBUG}")
endif()

set(GMOCK_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/gmock-1.7.0/include")
set(GMOCK_LIB_DIR "${CMAKE_BINARY_DIR}/bin")

set(GTEST_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/gmock-1.7.0/gtest/include")
set(GTEST_LIB_DIR "${CMAKE_BINARY_DIR}/bin")

message(STATUS "GMOCK_INCLUDE_DIR=${GMOCK_INCLUDE_DIR}")
message(STATUS "GTEST_INCLUDE_DIR=${GTEST_INCLUDE_DIR}")
message(STATUS "GMOCK_LIB_DIR=${GMOCK_LIB_DIR}")
message(STATUS "GTEST_LIB_DIR=${GTEST_LIB_DIR}")

add_subdirectory(gmock-1.7.0)
add_subdirectory(XLib)
add_subdirectory(zSearch)

# include(CTest)