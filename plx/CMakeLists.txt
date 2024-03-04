# to build:
# $ cmake -H. -Bbuild  # one time only
# $ cmake --build build

cmake_minimum_required(VERSION 3.22)

#-----------------------------------------------------------------------
# Project configuration
#-----------------------------------------------------------------------

set(PROJECT_NAME plx)
set(VERSION 0.1.0)
set(DESCRIPTION "Custom programming language for WSU CS497")
set(URL "http://github.com")
set(AUTHOR "Jeff Meunier")

#-----------------------------------------------------------------------
# Compiler configuration
#-----------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++-14")  # requires '-gdwarf-4' compiler option

project(${PROJECT_NAME}
        VERSION      ${VERSION}
        DESCRIPTION  ${DESCRIPTION}
        HOMEPAGE_URL ${URL}
        LANGUAGES    CXX)  # where CXX means C++

message("compile options: " ${COMPILE_OPTIONS})
include_directories("${CMAKE_CURRENT_LIST_DIR}")
set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/../bin)
set(CMAKE_KEEP_TEST_OUTPUTS ON)

# add_compile_options(-O0 -g -ggdb -Wall -Wextra -pedantic -Wswitch-enum -Werror -std=c++14)
#add_compile_options(-O0 -g -ggdb -Wall -Wextra -pedantic -Werror -std=c++14 -gdwarf-4)
add_compile_options(-O0 -g -ggdb -Wall -Wextra -pedantic -std=c++14 -gdwarf-4)

#-----------------------------------------------------------------------
# Source files
#-----------------------------------------------------------------------

set(EXEC_SRC_FILES
    plx/main.cpp
)

set(LIB_SRC_FILES
    plx/data/Array.cpp
    plx/data/HashTable.cpp
    plx/data/List.cpp
    plx/data/Queue.cpp
    plx/data/Triple.cpp
    plx/evaluator/Evaluator.cpp
    plx/expr/Identifier.cpp
    plx/expr/Do.cpp
    plx/expr/If.cpp
    plx/expr/Let.cpp
    plx/expr/LetIn.cpp
    plx/expr/Quote.cpp
    plx/literal/Boolean.cpp
    plx/literal/Integer.cpp
    plx/literal/Nil.cpp
    plx/literal/String.cpp
    plx/literal/Symbol.cpp
    plx/object/Globals.cpp
    plx/object/HashCode.cpp
    plx/object/Object.cpp
    plx/object/Symbolic.cpp
    plx/object/ThrowException.cpp
    plx/object/TypeIds.cpp
)

set(TEST_SRC_FILES
    plx/data/Array.test.cpp
    plx/data/HashTable.test.cpp
    plx/data/List.test.cpp
    plx/data/Queue.test.cpp
    plx/data/Triple.test.cpp
    plx/evaluator/Evaluator.test.cpp
    plx/expr/Identifier.test.cpp
    plx/expr/Do.test.cpp
    plx/expr/If.test.cpp
    plx/expr/Let.test.cpp
    plx/expr/LetIn.test.cpp
    plx/expr/Quote.test.cpp
    plx/literal/Boolean.test.cpp
    plx/literal/Integer.test.cpp
    plx/literal/Nil.test.cpp
    plx/literal/String.test.cpp
    plx/literal/Symbol.test.cpp
    plx/object/Globals.test.cpp
    plx/object/Object.test.cpp
    test/PlxTestFixture.cpp
    test/test_main.cpp
    test/TestUtils.cpp
)

# compile all the LIB_SRC_FILES files into a library
add_library(
    ${PROJECT_NAME}_lib
    ${LIB_SRC_FILES}
)

#-----------------------------------------------------------------------
# Main executable
#-----------------------------------------------------------------------

add_executable(
    ${PROJECT_NAME}
    ${EXEC_SRC_FILES}
)

target_link_libraries(
    ${PROJECT_NAME}
    ${PROJECT_NAME}_lib
)

#-----------------------------------------------------------------------
# Testing
#-----------------------------------------------------------------------

find_package(GTest REQUIRED)

set(TEST_EXE_NAME ${PROJECT_NAME}-test)

add_executable(
    ${TEST_EXE_NAME}
    ${TEST_SRC_FILES}
)

target_link_libraries(
    ${TEST_EXE_NAME}
    ${PROJECT_NAME}_lib
    GTest::GTest
)
