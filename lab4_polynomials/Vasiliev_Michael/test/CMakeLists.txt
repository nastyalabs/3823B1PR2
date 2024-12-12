set(target polynomials_test)

file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp" "../include/polynomials.cpp")

add_executable(${target} ${srcs} ${hdrs})
target_link_libraries(${target} gtest)
