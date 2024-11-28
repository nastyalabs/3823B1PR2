cmake_minimum_required(VERSION 2.8)

include_directories(include gtest)
set(CMAKE_CXX_STANDARD 23)

# BUILD
add_subdirectory(samples)
add_subdirectory(test)
add_subdirectory(gtest)