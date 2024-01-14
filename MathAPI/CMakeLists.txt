cmake_minimum_required(VERSION 3.27)
project(Physics_Engine CXX)

add_library(MathAPI Real.h Vec3.h
        quaternion.h)

set_target_properties(MathAPI PROPERTIES LINKER_LANGUAGE CXX)