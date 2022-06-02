cmake_minimum_required(VERSION 3.22)
project(stums C)

set(CMAKE_C_STANDARD 99)

add_executable(stums main.c StudentManagementSystem.h applicationRun.c)
