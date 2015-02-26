project(zSearchTests)

set(GMOCK_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../gmock-1.7.0/include")
set(GMOCK_LIB_DIR "${CMAKE_SOURCE_DIR}/../gmock-1.7.0-build")

set(GTEST_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../gmock-1.7.0/gtest/include")
set(GTEST_LIB_DIR "${CMAKE_SOURCE_DIR}/../gmock-1.7.0-build/gtest")

include_directories("${GTEST_INCLUDE_DIR}" "${GMOCK_INCLUDE_DIR}" "${CMAKE_SOURCE_DIR}")
link_directories("${GTEST_LIB_DIR}" "${GMOCK_LIB_DIR}")

macro(CreateTestProj name fileName)
    add_executable(${name} ${fileName})
    target_link_libraries(${name} gmock.lib gtest.lib zSearch)
    add_test(NAME ${name} COMMAND ${name})
endmacro(CreateTestProj)

# CreateTestProj(test_1 test1.cpp)
# CreateTestProj(test_2 test2.cpp)