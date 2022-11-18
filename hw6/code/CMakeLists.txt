# CMake version, project name
cmake_minimum_required(VERSION 3.10)
project(ConwaysLife)

#
# Manually specifying all the header files.
#
set(HEADER_FILES
    rlutil.h
    RendererConsole.hpp
    Renderer.hpp
    PatternGosperGliderGun.hpp
    PatternGlider.hpp
    PatternBlock.hpp
    PatternBlinker.hpp
    PatternAcorn.hpp
    Pattern.hpp
    LifeSimulator.hpp)

#
# Manually specifying all the source files.
#
set(SOURCE_FILES
    RendererConsole.cpp
    PatternGosperGliderGun.cpp
    PatternGlider.cpp
    PatternBlock.cpp
    PatternBlinker.cpp
    PatternAcorn.cpp
    LifeSimulator.cpp)

#
# This is the main target
#
add_executable(ConwaysLife ${HEADER_FILES} ${SOURCE_FILES} main.cpp)

#
# We want the C++ 17 standard for our project
#
set_property(TARGET ConwaysLife PROPERTY CXX_STANDARD 17)
#set_property(TARGET UnitTestRunner PROPERTY CXX_STANDARD 17)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    target_compile_options(ConwaysLife PRIVATE /W4 /permissive-)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options(ConwaysLife PRIVATE -Wall -Wextra -pedantic)    
endif()

#
# Prepare a pre-build step to run clang-format over all the [ch]pp source files.
# Start by finding the location of the clang-format executable.
#
find_program(CLANG_FORMAT "clang-format")
if (CLANG_FORMAT)
    #
    # Need to take the simple source file locations used for the project and get their full
    # file system locations for use in putting together the clang-format command line
    #
    unset(SOURCE_FILES_PATHS)
    foreach(SOURCE_FILE ${HEADER_FILES} ${SOURCE_FILES} main.cpp)
        get_source_file_property(WHERE ${SOURCE_FILE} LOCATION)
        set(SOURCE_FILES_PATHS ${SOURCE_FILES_PATHS} ${WHERE})
    endforeach()

    #
    # This creates the clang-format target/command
    #
    add_custom_target(
        ClangFormat
        COMMAND ${CLANG_FORMAT}
        -i
        -style=file
        ${SOURCE_FILES_PATHS}
    )
    #
    # This makes the clang-format target a dependency of the main ConwaysLife project
    #
    add_dependencies(ConwaysLife ClangFormat)
else()
    message("Unable to find clang-format")
endif()