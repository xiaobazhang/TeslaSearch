cmake_minimum_required(VERSION 3.5)
project(TiAlloy)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__FILENAME__='\"$(subst ${CMAKE_SOURCE_DIR}/,,$(abspath $<))\"'")
add_definitions("-DLINUX -g -O2 -std=c++11")

aux_source_directory(./srv DES_SRC)
aux_source_directory(./srv/base/test DES_SRC)

add_executable(algo ${DES_SRC} srv/base/Ti_Singleton.h srv/base/Ti_Lock.h srv/base/Ti_Thread.h srv/base/log/Ti_LogBuff.cc srv/base/log/Ti_LogBuff.h srv/base/Ti_NoCopy.h srv/base/Ti_Trie.h)
