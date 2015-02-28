macro(_Init isLibrary)
    message(STATUS "PROJECT: ${PROJECT_NAME}")
    set(G_INCLUDE_DIRS)
    set(G_LINK_DIRS)
    set(G_LINK_TARGETS)
    set(G_IS_LIBRARY ${isLibrary})
endmacro(_Init)

macro(InitExe)
    _Init(FALSE)
endmacro(InitExe)

macro(InitLib)
    _Init(TRUE)
endmacro(InitLib)

macro(_CreateTestProj name fileName)
    add_executable(${name} ${fileName})
    target_link_libraries(${name} gmock gmock_main gtest gtest_main XLib ${G_LINK_TARGETS})
    add_test(NAME ${name} COMMAND ${name})
endmacro(_CreateTestProj)

macro(CreateTests prefix)
    include_directories("${GTEST_INCLUDE_DIR}" "${GMOCK_INCLUDE_DIR}" ${G_INCLUDE_DIRS})
    link_directories("${GTEST_LIB_DIR}" "${GMOCK_LIB_DIR}")

    file(GLOB_RECURSE CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}" "*.cpp")
    source_group("Test" FILES ${CPP_FILES})

    foreach(curItem ${CPP_FILES})
        get_filename_component(displayName "${curItem}" NAME_WE)
        _CreateTestProj("${prefix}${displayName}" ${curItem})
    endforeach()
endmacro(CreateTests)

macro (CreateProject name)
    configure_file ("${PROJECT_SOURCE_DIR}/Version.h.in" "${PROJECT_BINARY_DIR}/Generated/Version.h")
    include_directories("${PROJECT_BINARY_DIR}/Generated" ${G_INCLUDE_DIRS})
    
    message(STATUS "copied Version.h to: ${PROJECT_BINARY_DIR}/Generated/Version.h")

    file(GLOB_RECURSE CPP_FILES "${PROJECT_SOURCE_DIR}" "*.cpp")
    file(GLOB_RECURSE H_FILES "${PROJECT_SOURCE_DIR}" "*.h")
    source_group("Code" FILES ${CPP_FILES} ${H_FILES})
    
    set(todoFile)
    
    if(EXISTS "${PROJECT_SOURCE_DIR}/TODO.txt")
        set(todoFile TODO.txt)
    endif()

    if(${G_IS_LIBRARY})
        message(STATUS "BUILDING ${PROJECT_NAME} as: LIBRARY")
        add_library(${name} ${PROJ_LIB_TYPES} ${CPP_FILES} ${H_FILES} ${todoFile})
        message(STATUS "building ${name} libray as: ${PROJ_LIB_TYPES}")
    else()
        message(STATUS "BUILDING ${PROJECT_NAME} as: EXE")
        add_executable(${name} ${CPP_FILES} ${H_FILES})
        target_link_libraries(${name} ${G_LINK_DIRS})
    endif()
endmacro(CreateProject)