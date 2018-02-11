cmake_minimum_required(VERSION 3.5)
project(algo)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__FILENAME__='\"$(subst ${CMAKE_SOURCE_DIR}/,,$(abspath $<))\"'")
add_definitions("-DLINUX -g -O2 -std=c++11")

aux_source_directory(. DES_SRC)
add_executable(algo ${DES_SRC})
