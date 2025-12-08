cmake_minimum_required(VERSION 3.19)

project(aoc CXX)

set(CMAKE_CXX_STANDARD 23)

function(add_day dayname)
    add_executable(${dayname} ${ARGN})
    target_link_libraries(${dayname} PRIVATE aoc_common)
endfunction()

add_subdirectory(common)
add_subdirectory(day01)
add_subdirectory(day02)
add_subdirectory(day03)
add_subdirectory(day04)
add_subdirectory(day05)
add_subdirectory(day06)
add_subdirectory(day07)
add_subdirectory(day08)
