cmake_minimum_required(VERSION 3.27)
project(Physics_Engine CXX)

set(CMAKE_CXX_STANDARD 23)
add_subdirectory(MathAPI)

add_executable(Physics_Engine main.cpp)

set_target_properties(Physics_Engine PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(Physics_Engine PUBLIC MathAPI)