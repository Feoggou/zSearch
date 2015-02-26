macro(CreateTestProj name fileName)
    add_executable(${name} ${fileName})
    target_link_libraries(${name} gmock gmock_main gtest gtest_main XLib ${ARGN})
    add_test(NAME ${name} COMMAND ${name})
endmacro(CreateTestProj)