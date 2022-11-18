cmake_minimum_required(VERSION 3.10)
project(vs_proj_HW1_withCmake)


# Step 1 - Files variable
#----------------------------------------------------------------------------
set(SOURCE_FILES Assignment1.cpp)

# This will make a Visual Studio project called Assignment1
add_executable(exeName ${SOURCE_FILES})
set_property(TARGET exeName PROPERTY CXX_STANDARD 17)


# Step 2 - Fing clang-format (this should work since LLVM is in our PATH)
#----------------------------------------------------------------------------
# There is a CMake script that goes and looks for clang-format.
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
        add_dependencies(exeName ClangFormat)
    else()
        message("Unable to find clang-format")
endif()



#[[
find_program(CLANG_FORMAT "clang-format")
if (CLANG_FORMAT)
    unset(SOURCE_FILES_PATHS)
    foreach(SOURCE_FILE ${SOURCE_FILES})
        get_source_file_property(WHERE ${SOURCE_FILE} LOCATION)
        set(SOURCE_FILES_PATHS ${SOURCE_FILES_PATHS} ${WHERE})
    endforeach()
    add_custom_target(
        ClangFormat
        COMMAND ${CLANG_FORMAT}
        -i
        -style=file
        ${SOURCE_FILES_PATHS})
    add_dependencies(HelloWorld ClangFormat)
endif()
]]