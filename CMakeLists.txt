# This CMakeLists.txt file sets the minimum required version of CMake to 3.10.
cmake_minimum_required(VERSION 3.10)

# ==============================================================================
# Project: TreeCode
# ==============================================================================
#  _____ ____  _____ _____ ____ ___  ____  _____ 
# |_   _|  _ \| ____| ____/ ___/ _ \|  _ \| ____|
#   | | | |_) |  _| |  _|| |  | | | | | | |  _|  
#   | | |  _ <| |___| |__| |__| |_| | |_| | |___ 
#   |_| |_| \_|_____|_____\____\___/|____/|_____|
# 
# Licensed under the MIT License <http://opensource.org/licenses/MIT>.
# SPDX-License-Identifier: MIT
# TREECODE - Copyright (c) - Amr MOUSA 2025-2026
# ==============================================================================
#
# File: CMakeLists.txt
# Description: This project is a C++ library for managing hierarchical data
# structures. It includes classes for containers, elements, groups, templates,
# and logging. The library can be built as a shared library and includes options
# for building tests and examples.
#
# Author: Amr MOUSA
# License: MIT License
# Version: 0.0.1
# Date: 7 February 2025
#
# ==============================================================================

# Set the project name
project(TreeCode LANGUAGES CXX)

# Set the C++ standard to C++17
# Ensure that the C++ standard is required
# Disable compiler-specific extensions
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# This CMakeLists.txt file configures compiler-specific options and flags.
# 
# If the compiler is MSVC (Microsoft Visual C++):
# - Adds compile options: /W4 (warning level 4), /permissive- (standards conformance), /Zc:__cplusplus (correct __cplusplus macro value).
# - Sets release mode flags to include /O2 (optimize for speed) and /DNDEBUG (disable debugging).
#
# If the compiler is GNU (GCC):
# - Adds compile options: -Wall (enable all warnings), -Wextra (enable extra warnings), -pedantic (strict ISO compliance), -Werror (treat warnings as errors).
# - Sets release mode flags to include -O3 (optimize for speed) and -DNDEBUG (disable debugging).
#
# If the compiler is Clang:
# - Adds compile options: -Wall (enable all warnings), -Wextra (enable extra warnings), -pedantic (strict ISO compliance), -Werror (treat warnings as errors).
# - Sets release mode flags to include -O3 (optimize for speed) and -DNDEBUG (disable debugging).
#
# If the compiler is Intel:
# - Adds compile options: -Wall (enable all warnings), -Wextra (enable extra warnings), -pedantic (strict ISO compliance), -Werror (treat warnings as errors).
# - Sets release mode flags to include -O3 (optimize for speed) and -DNDEBUG (disable debugging).
if(MSVC)
    add_compile_options(/W4 /permissive- /Zc:__cplusplus)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /DNDEBUG")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wall -Wextra -pedantic -Werror)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wall -Wextra -pedantic -Werror)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    add_compile_options(-Wall -Wextra -pedantic -Werror)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
endif()

# Option to enable or disable the building of tests.
# If set to ON, tests will be built. Default is OFF.
# Usage: -DBUILD_TESTS=ON
option(BUILD_TESTS "Build tests" OFF)

# Option to enable or disable the building of examples.
# If set to ON, examples will be built. Default is ON.
# Usage: -DBUILD_EXAMPLES=ON
option(BUILD_EXAMPLES "Build examples" ON)

# Recursively collects all .cpp source files located in the src/core directory
# and stores their paths in the LIB_SOURCES variable.
file(GLOB_RECURSE LIB_SOURCES "src/core/*.cpp")

# Include the directory src/core/includes in the list of directories
# that will be searched for header files during the compilation process.
include_directories(src/core/includes)

# Adds a shared library target to the project.
# The library will be named as the project name with 'Lib' appended.
# The source files for the library are specified in the LIB_SOURCES variable.
add_library(${CMAKE_PROJECT_NAME}Lib SHARED ${LIB_SOURCES})

# Set the binary directory based on the source directory and build type.
# This will place the binaries in a subdirectory named 'binaries' within the source directory,
# with a further subdirectory for the specific build type (e.g., Debug, Release).
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/binaries/${CMAKE_BUILD_TYPE})

# Set the output directories for the target properties of the project library.
# ARCHIVE_OUTPUT_DIRECTORY: Directory for static library files (.lib, .a).
# LIBRARY_OUTPUT_DIRECTORY: Directory for shared library files (.dll, .so).
# RUNTIME_OUTPUT_DIRECTORY: Directory for executable files (.exe, .out).
# OUTPUT_NAME: The base name for the output files, set to the project name.
if(MSVC)
    set_target_properties(${CMAKE_PROJECT_NAME}Lib PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/binaries/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/binaries/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/binaries/bin"
        OUTPUT_NAME "${CMAKE_PROJECT_NAME}"
    )
else()
    set_target_properties(${CMAKE_PROJECT_NAME}Lib PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        OUTPUT_NAME "${CMAKE_PROJECT_NAME}"
    )
endif()


# Install the library target of the project.
# - ARCHIVE: Specifies the destination directory for archive files (e.g., static libraries).
# - LIBRARY: Specifies the destination directory for library files (e.g., shared libraries).
# - RUNTIME: Specifies the destination directory for runtime files (e.g., executables).
install(TARGETS ${CMAKE_PROJECT_NAME}Lib
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

# Install header files from the src/core/includes/ directory to the include directory.
# - FILES_MATCHING: Ensures only files matching the specified pattern are installed.
# - PATTERN "*.hpp": Specifies that only files with the .hpp extension are installed.
install(DIRECTORY src/core/includes/ DESTINATION include
    FILES_MATCHING PATTERN "*.hpp"
)

# This CMake script checks if the BUILD_TESTS option is enabled.
# If BUILD_TESTS is enabled:
#   - It enables testing using the enable_testing() command.
#   - It checks if a CMakeLists.txt file exists in the "tests" directory.
#     - If the file exists, it adds the "tests" subdirectory to the build.
#     - If the file does not exist, it issues a warning message indicating that the "tests" directory does not exist or does not contain a CMakeLists.txt file.
# If BUILD_TESTS is not enabled, it outputs a message indicating that running tests is not enabled.
if(BUILD_TESTS)
    enable_testing()
    if(EXISTS "${CMAKE_SOURCE_DIR}/tests/CMakeLists.txt")
        add_subdirectory(tests)
    else()
        message(WARNING "\"tests\" directory does not exist or not contain a CmakeLists.txt file.")
    endif()
else()
    message("-- Running tests is not enabled.")
endif()

# This CMake script checks if the BUILD_EXAMPLES option is enabled.
# If enabled, it verifies the existence of a CMakeLists.txt file in the "examples" directory.
# If the file exists, it adds the "examples" directory as a subdirectory to the build.
# If the file does not exist, it issues a warning message.
# If BUILD_EXAMPLES is not enabled, it outputs a message indicating that building examples is not enabled.
if(BUILD_EXAMPLES)
    if(EXISTS "${CMAKE_SOURCE_DIR}/examples/CMakeLists.txt")
        add_subdirectory(examples)
    else()
        message(WARNING "\"examples\" directory does not exist or not contain a CmakeLists.txt file.")
    endif()
else()
    message("-- Building examples is not enabled.")
endif()