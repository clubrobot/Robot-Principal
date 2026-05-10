cmake_minimum_required(VERSION 4.2)
project(grafcet)

add_library(grafcet STATIC src/StateMachine.cpp)
target_include_directories(grafcet PUBLIC include)
target_compile_features(grafcet PUBLIC cxx_std_23)
add_library(grafcet::grafcet ALIAS grafcet)