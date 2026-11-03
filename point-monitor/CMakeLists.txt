# Build for the point machine monitor (Challenge 3). From the repository root:
#
#   cmake -S point-monitor -B build-pm
#   cmake --build build-pm
#   ctest --test-dir build-pm -C Debug
#
# You do not need to edit this file. It builds tests/test_monitor.c as soon
# as the file exists: add it and build again.
cmake_minimum_required(VERSION 3.16)
project(point_monitor LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -pedantic)
endif()

include_directories(. tests)

# The monitor, linked with the stand-in monitoring unit in mu.c.
add_executable(monitor_app main.c grade.c monitor.c mu.c)

# Tests never link mu.c. The monitor tests link the fake monitoring unit
# in tests/fake_mu.c instead.
enable_testing()

# Makes the next build run CMake again when a test file appears.
file(GLOB test_files CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_*.c)

add_executable(test_grade tests/test_grade.c grade.c)
add_test(NAME grade COMMAND test_grade)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_monitor.c)
  add_executable(test_monitor tests/test_monitor.c monitor.c grade.c tests/fake_mu.c)
  add_test(NAME monitor COMMAND test_monitor)
endif()

# Reference tests for Challenge 3. Off by default, so they do not give the
# answers away. Turn them on with -DWITH_SOLUTION=ON.
option(WITH_SOLUTION "Also build the reference tests for Challenge 3" OFF)
if(WITH_SOLUTION)
  set(solution ${CMAKE_CURRENT_SOURCE_DIR}/../challenges/03-point-monitor/solution)

  add_executable(solution_test_monitor
    ${solution}/test_monitor.c monitor.c grade.c tests/fake_mu.c)
  add_test(NAME solution_monitor COMMAND solution_test_monitor)
endif()
