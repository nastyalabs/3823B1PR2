set(target ${MP2_LIBRARY})

file(GLOB hdrs "${MP2_INCLUDE}/*.h*")
file(GLOB interp "${MP2_INCLUDE}/*.interp")
file(GLOB tokens "${MP2_INCLUDE}/*.tokens")
file(GLOB srcs "*.cpp" "${MP2_INCLUDE}/*.cpp")

add_executable(${target} ${srcs} ${hdrs} ${interp} ${tokens})

include_directories(${target} ${ANTLR_INCLUDE_DIR})
include_directories(${target} ${antlr4-runtime_DIR})

target_link_libraries(${target} "${ANTLR4_LIB_DIR}/antlr4-runtime.lib")

add_custom_command(TARGET ${target}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy ${antlr4-runtime_DIR}/bin/bin/antlr4-runtime.dll ${CMAKE_BINARY_DIR}/bin/
)