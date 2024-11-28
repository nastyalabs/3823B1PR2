set(target queue_test)

file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp" "../include/queue.cpp")

add_executable(${target} ${srcs} ${hdrs})
target_link_libraries(${target} gtest)
