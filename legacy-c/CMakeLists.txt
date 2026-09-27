# Build for the legacy C challenge. From the repository root:
#
#   cmake -S legacy-c -B build
#   cmake --build build
#   ctest --test-dir build -C Debug
#
# You do not need to edit this file. It builds a test program for every
# test file in tests/: add tests/test_route.c or tests/test_sorter.c and
# build again.
cmake_minimum_required(VERSION 3.16)
project(legacy_sorter LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -pedantic)
endif()

include_directories(. tests)

# The legacy program, linked with the stand-in hardware in hw.c.
add_executable(sorter_app main.c checksum.c route.c sorter.c hw.c)

# Tests never link hw.c. The sorter tests link the fake hardware in
# tests/fake_hw.c instead.
enable_testing()

# Makes the next build run CMake again when a test file appears.
file(GLOB test_files CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_*.c)

add_executable(test_checksum tests/test_checksum.c checksum.c)
add_test(NAME checksum COMMAND test_checksum)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_route.c)
  add_executable(test_route tests/test_route.c route.c)
  add_test(NAME route COMMAND test_route)
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_sorter.c)
  add_executable(test_sorter
    tests/test_sorter.c sorter.c checksum.c route.c tests/fake_hw.c)
  add_test(NAME sorter COMMAND test_sorter)
endif()

# Reference tests for Challenge 1. Off by default, so they do not give the
# answers away. Turn them on with -DWITH_SOLUTION=ON.
option(WITH_SOLUTION "Also build the reference tests for Challenge 1" OFF)
if(WITH_SOLUTION)
  set(solution ${CMAKE_CURRENT_SOURCE_DIR}/../challenges/01-legacy-c-testable/solution)

  add_executable(solution_test_route ${solution}/test_route.c route.c)
  add_test(NAME solution_route COMMAND solution_test_route)

  add_executable(solution_test_sorter
    ${solution}/test_sorter.c sorter.c checksum.c route.c tests/fake_hw.c)
  add_test(NAME solution_sorter COMMAND solution_test_sorter)
endif()
