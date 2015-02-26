project (cZSearch VERSION 0.0.0.0)

configure_file ("${PROJECT_SOURCE_DIR}/Version.h.in" "${PROJECT_SOURCE_DIR}/Version.h")

include_directories("${CMAKE_SOURCE_DIR}/../XLib")
link_directories("${CMAKE_SOURCE_DIR}/../XLib/bin")

add_executable(cZSearch cZSearch.cpp)
target_link_libraries(cZSearch zSearch)