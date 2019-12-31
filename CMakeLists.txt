cmake_minimum_required(VERSION 3.5)

project(ZyniacCommandInterface VERSION 0.1 DESCRIPTION "The Command Interface for Zyniac")

if(DEFINED $ENV{Boost_ROOT}) # Windows Boost Path
	cmake_policy(SET CMP0074 NEW)
endif()

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(MADE_BUILD FALSE)
set(MADE_TEST_BUILD FALSE)
set(MADE_LIBRARY_BUILD FALSE)

# ---------------------------------

# This function points to the include directories. It is nomally included in genexe and genlib
function(addincdirs linkname)
    target_include_directories(${linkname} PUBLIC ${IncludeDirs})
    target_link_directories(${linkname} PUBLIC ${LibraryDirs})
    target_link_libraries(${linkname} PUBLIC ${Libraries})
    target_compile_definitions(${linkname} PUBLIC PRERESERVE_COMMANDS=5 CMD_MIN_LENGTH=2)
    set_target_properties(${linkname} PROPERTIES
                CXX_STANDARD 17
                CXX_STANDARD_REQUIRED ON)
endfunction()

# Generates a test executeable and points to the include files to compile the project correctly
function(genexe)
    add_executable(testexe ${ExeFiles})
    addincdirs(testexe)
    set(MADE_BUILD TRUE PARENT_SCOPE)
    set(MADE_TEST_BUILD TRUE PARENT_SCOPE)
endfunction()

# Generates the library and points to the include files to compile the project correctly
function(genlib)
    add_library(commandinterpreter ${LibFiles})
    addincdirs(commandinterpreter)
    set(MADE_BUILD TRUE PARENT_SCOPE)
    set(MADE_LIBRARY_BUILD TRUE PARENT_SCOPE)
endfunction()

# ---------------------------------

set(IncludeDir "${CMAKE_SOURCE_DIR}/Include/")
set(SourceDir "${CMAKE_SOURCE_DIR}/src/")

find_package(Boost REQUIRED)

set(IncludeDirs ${IncludeDir} ${Boost_INCLUDE_DIRS})
set(LibraryDirs ${Boost_LIBRARY_DIRS})
set(Libraries ${Boost_LIBRARIES})

file(GLOB_RECURSE IncludeFiles "${IncludeDir}*.h")
file(GLOB_RECURSE SourceFiles "${SourceDir}*.cpp")

set(MainFile "${CMAKE_SOURCE_DIR}/src/main.cpp")

set(LibFiles ${SourceFiles})
set(ExeFiles ${IncludeFiles} ${SourceFiles})

list(LENGTH LibFiles liblength)
list(FIND LibFiles ${MainFile} LibContainsMain)

if(liblength GREATER 1)

    list(REMOVE_ITEM LibFiles ${MainFile})

    if(${LibContainsMain} GREATER -1)
        message(STATUS "Generating TEST executable and LIBRARY")
        genexe()
        genlib()
    else()
        message(STATUS "Generating only LIBRARY, TEST NOT FOUND")
        genlib()
    endif()

else()
    message(STATUS "FILES ARE MISSING")
    if(liblength EQUAL 1 AND ${LibContainsMain} GREATER -1) # AND LibContainsMain
        message(STATUS "CANNOT generate LIBRARY because files are missing, BUT TEST can generate")
        genexe()
    endif()
endif()

if(MADE_BUILD)
    message(STATUS "Build files will be written to")
    if(MADE_LIBRARY_BUILD)
        message(STATUS "    - Library DIR: ${LIBRARY_OUTPUT_PATH}")
    endif()

    if(MADE_TEST_BUILD)
        message(STATUS "    - Executable DIR: ${EXECUTABLE_OUTPUT_PATH}")
    endif()
else()
    message(STATUS "Build failed")
endif()