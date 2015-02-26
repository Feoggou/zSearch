cmake_minimum_required (VERSION 3.1)

option(PROJ_LIB_TYPES "Use zSearch and XLib as static libs." "STATIC")
if (NOT PROJ_LIB_TYPES)
    set(PROJ_LIB_TYPES "STATIC")
endif()
message(STATUS "PROJ_LIB_TYPES=${PROJ_LIB_TYPES}")

enable_testing()

project(zSearchApp)
message(STATUS "link libs as: ${PROJ_LIB_TYPES}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY    ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY    ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY    ${CMAKE_BINARY_DIR}/bin)

if (MSVC)
    set(CFLAG CMAKE_CXX_FLAGS_DEBUG)
    string(REPLACE "/MD" "/MT" ${CFLAG} "${${CFLAG}}")
    message(STATUS "link flags: ${CMAKE_CXX_FLAGS_DEBUG}")
endif()

add_subdirectory(cZSearch)
add_subdirectory(zSearch)
add_subdirectory(Tests)

# include(CTest)