project (cZSearch VERSION 0.0.0.0)

configure_file ("${PROJECT_SOURCE_DIR}/Version.h.in" "${PROJECT_BINARY_DIR}/Generated/Version.h")

include_directories("${CMAKE_SOURCE_DIR}/../XLib" "${PROJECT_BINARY_DIR}/Generated")
link_directories("${CMAKE_SOURCE_DIR}/../XLib/bin")

add_executable(cZSearch cZSearch.cpp)
target_link_libraries(cZSearch zSearch)