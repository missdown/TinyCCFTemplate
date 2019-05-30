cmake_minimum_required(VERSION 3.10)
project(ACM_template)


#set(CMAKE_CXX_COMPILER “/usr/bin/arm-none-eabi-g++”)
set(CMAKE_CXX_STANDARD 11)
add_definitions("-Wall -g -O0")
add_executable(ACM_template main.cpp sort/Sort.h nt/nt.h Search/search.h Graph/Graph.h Graph/sp.h dp/dp.h String/string.h tree/AdvanceTree.h)