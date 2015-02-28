macro(CreateTestProj name fileName)
    add_executable(${name} ${fileName})
    target_link_libraries(${name} gmock gmock_main gtest gtest_main XLib ${ARGN})
    add_test(NAME ${name} COMMAND ${name})
endmacro(CreateTestProj)

macro(CreateTests prefix addIncludeDirs addLinkTargets)
    include_directories("${GTEST_INCLUDE_DIR}" "${GMOCK_INCLUDE_DIR}" "${addIncludeDirs}")
    link_directories("${GTEST_LIB_DIR}" "${GMOCK_LIB_DIR}")

    file(GLOB_RECURSE CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}" "*.cpp")
    source_group("Test" FILES ${CPP_FILES})

    foreach(curItem ${CPP_FILES})
        get_filename_component(displayName "${curItem}" NAME_WE)
        CreateTestProj("${prefix}${displayName}" ${curItem} ${addLinkTargets})
    endforeach()
endmacro(CreateTests)