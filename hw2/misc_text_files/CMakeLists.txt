#----------------------------------------------------------------------------
#----------------------------------------------------------------------------
# CS 3460, hw2 - Random Distributions
# Due: 09/20/2019 at 11:59 pm
# Author: Jared Hansen
#----------------------------------------------------------------------------
#----------------------------------------------------------------------------


# Step 0 - Specify minimum version of CMake, specify a project name
#----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)
project(RandDistributions)


# Step 1 - Define SOURCE_FILES variable, add exe, set compiler to C++17
#----------------------------------------------------------------------------
set(SOURCE_FILES Assignment2.cpp)
add_executable(RandDistributions ${SOURCE_FILES})
set_property(TARGET RandDistributions PROPERTY CXX_STANDARD 17)


# Step 2 - Find clang-format
#----------------------------------------------------------------------------
# ALWAYS INCLUDE THE _clang-format.txt IN THE SAME DIRECTORY AS YOUR PROJECT
find_program(CLANG_FORMAT "clang-format")
if (CLANG_FORMAT)
    message("clang-format found at: " ${CLANG_FORMAT})
    # In case there were other source files, unset the paths
    unset(SOURCE_FILES_PATHS)
        foreach(SOURCE_FILE ${SOURCE_FILES})
            get_source_file_property(WHERE ${SOURCE_FILE} LOCATION)
            message("file location   " ${WHERE})
            set(SOURCE_FILES_PATHS ${SOURCE_FILES_PATHS} ${WHERE})
        endforeach()

        # This creates the clang-format target/command
        add_custom_target(
            ClangFormat
            COMMAND ${CLANG_FORMAT}
            -i
            -style=file
            ${SOURCE_FILES_PATHS})

        # This makes the clang-format target a dependency of the main project
        add_dependencies(RandDistributions ClangFormat)
    else()
        message("Unable to find clang-format")
endif()



# Step 3 - Enable compiler warnings for MSVC and g++
#----------------------------------------------------------------------------
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    target_compile_options(RandDistributions PRIVATE /W4 /permissive-)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options(RandDistributions PRIVATE -Wall -Wextra -pedantic)
endif()