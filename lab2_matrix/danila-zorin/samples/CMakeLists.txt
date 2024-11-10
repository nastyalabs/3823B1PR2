file(GLOB hdrs "*.h*" "..danila-zorinn/include/*.h")
file(GLOB srcs "*.cpp")

add_executable(matrix ${srcs} ${hdrs})