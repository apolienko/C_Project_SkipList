cmake_minimum_required(VERSION 3.19)
project(C_Project_SkipList C)

set(CMAKE_C_STANDARD 99)

add_executable(C_Project_SkipList main.c SkipList.h SkipList.c)