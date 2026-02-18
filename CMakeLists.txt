# current version on my mint is 3.26
cmake_minimum_required(VERSION 3.26.0)

# Project name
project(LC3VM)

# set source file and compiler path
set(src main.c)
set(CMAKE_C_COMPILER "/usr/bin/clang")

# where to add
add_executable(LC3VM file_memory.c trap.c opcodes.c main.c)
