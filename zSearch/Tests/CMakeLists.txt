project(zSearchTests)

include_directories("${GTEST_INCLUDE_DIR}" "${GMOCK_INCLUDE_DIR}" "${CMAKE_SOURCE_DIR}/zSearch")
link_directories("${GTEST_LIB_DIR}" "${GMOCK_LIB_DIR}")

CreateTestProj(S_test_1 test1.cpp)
CreateTestProj(S_test_2 test2.cpp)