project (zSearch VERSION 0.0.0.0)

option (USE_MYMATH "Use tutorial provided math implementation" ON) 
        
configure_file ("${PROJECT_SOURCE_DIR}/Version.h.in" "${PROJECT_SOURCE_DIR}/Version.h")

file(GLOB_RECURSE CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}" "*.cpp")
file(GLOB_RECURSE H_FILES "${CMAKE_CURRENT_SOURCE_DIR}" "*.h")

source_group("Code" FILES ${CPP_FILES} ${H_FILES})

add_library(zSearch ${PROJ_LIB_TYPES} ${CPP_FILES} ${H_FILES})
message(STATUS "building zSearch libray as: ${PROJ_LIB_TYPES}")