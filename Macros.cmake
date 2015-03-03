# Copyright 2015 Samuel Ghineț
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

macro(_Init isLibrary)
    message(STATUS "PROJECT: ${PROJECT_NAME}")
    set(G_INCLUDE_DIRS ${PROJECT_SOURCE_DIR})
    set(G_LINK_DIRS)
    set(G_LINK_TARGETS)
    set(G_IS_LIBRARY ${isLibrary})
    
    if ("${PROJ_LIB_TYPES}" STREQUAL "SHARED")
        add_definitions("-DPROJ_LINK_SHARED=1")
    else()
        add_definitions("-DPROJ_LINK_SHARED=0")
    endif()
endmacro(_Init)

macro(InitExe)
    _Init(FALSE)
endmacro(InitExe)

macro(InitLib)
    _Init(TRUE)
endmacro(InitLib)

macro(_CreateTestProj name fileName)
    SetLinkFlags()
    message(STATUS "building test: ${name}")
    add_executable(${name} ${fileName})
    target_link_libraries(${name} gmock gmock_main gtest gtest_main XLib ${G_LINK_TARGETS})
    add_test(NAME ${name} COMMAND ${name})
endmacro(_CreateTestProj)

macro(CreateTests prefix)
    if ("${PROJ_LIB_TYPES}" STREQUAL "STATIC")
        list(APPEND G_INCLUDE_DIRS "${GTEST_INCLUDE_DIR}" "${GMOCK_INCLUDE_DIR}")
        list(APPEND G_LINK_DIRS "${GTEST_LIB_DIR}" "${GMOCK_LIB_DIR}")

        include_directories(${G_INCLUDE_DIRS})
        link_directories(${G_LINK_DIRS})

        file(GLOB CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}" "*.cpp")
        source_group("Test" FILES ${CPP_FILES})

        foreach(curItem ${CPP_FILES})
            if (NOT IS_DIRECTORY "${curItem}")
                get_filename_component(displayName "${curItem}" NAME_WE)
                _CreateTestProj("${prefix}${displayName}" ${curItem})
            endif()
        endforeach()
    endif()
endmacro(CreateTests)

macro (CreateProject name)
    configure_file ("${PROJECT_SOURCE_DIR}/Version.h.in" "${PROJECT_BINARY_DIR}/Generated/Version.h")

    if (WIN32)
	set(platformDir "Win")
    elseif(UNIX AND NOT APPLE)
	set(platformDir "Linux")
    endif()
    
    SetLinkFlags()

    list(APPEND G_INCLUDE_DIRS "${platformDir}" "${PROJECT_BINARY_DIR}/Generated")
    include_directories(${G_INCLUDE_DIRS})
    link_directories(${G_LINK_DIRS})

    file(GLOB cppFiles "*.cpp")
    file(GLOB hFiles "*.h")
    source_group("Code" FILES ${cppFiles} ${hFiles})

    file(GLOB platfromCppFiles "${platformDir}/*.cpp")
    file(GLOB platfromHFiles "${platformDir}/*.h")
    source_group("Code/${platformDir}" FILES ${platfromCppFiles} ${platfromHFiles})

    set(srcFiles ${cppFiles} ${hFiles} ${platfromCppFiles} ${platfromHFiles})
    message(STATUS "files: ${srcFiles}")
    
    set(todoFile)
    
    if(EXISTS "${PROJECT_SOURCE_DIR}/TODO.txt")
        set(todoFile TODO.txt)
    endif()

    if(${G_IS_LIBRARY})
        if ("${PROJ_LIB_TYPES}" STREQUAL "SHARED")
            STRING(TOUPPER ${PROJECT_NAME} ucaseProjName)
            add_definitions("-D${ucaseProjName}_EXPORTS")
        endif()
        
        message(STATUS "building ${name} libray as: ${PROJ_LIB_TYPES}")
        add_library(${name} ${PROJ_LIB_TYPES} ${srcFiles} ${todoFile})
        
        if ("${PROJ_LIB_TYPES}" STREQUAL "SHARED")
            target_link_libraries(${name} ${G_LINK_TARGETS})
        endif()
    else()
        message(STATUS "building exe ${name}")
        add_executable(${name} ${srcFiles})
        target_link_libraries(${name} ${G_LINK_TARGETS})
    endif()
endmacro(CreateProject)


macro(SetLinkFlags)
    if (MSVC)
        set(cflagsDbg CMAKE_CXX_FLAGS_DEBUG)
        set(cflagsRl CMAKE_CXX_FLAGS_RELEASE)
        message(STATUS "VC PROJECT -- ${PROJECT_NAME}: OLD link flags: ${CMAKE_CXX_FLAGS_DEBUG}")
        if("${PROJ_LIB_TYPES}" STREQUAL "STATIC")
            string(REPLACE "/MD" "/MT" ${cflagsDbg} "${${cflagsDbg}}")
            string(REPLACE "/MD" "/MT" ${cflagsRl} "${${cflagsRl}}")
        else()
            string(REPLACE "/MT" "/MD" ${cflagsDbg} "${${cflagsDbg}}")
            string(REPLACE "/MT" "/MD" ${cflagsRl} "${${cflagsRl}}")
        endif()
        message(STATUS "VC PROJECT -- ${PROJECT_NAME}: link flags: ${CMAKE_CXX_FLAGS_DEBUG}")
    endif()
endmacro(SetLinkFlags)