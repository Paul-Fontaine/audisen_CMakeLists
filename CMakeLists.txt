cmake_minimum_required(VERSION 3.18)
project(audisen_debug C)

set(CMAKE_C_STANDARD 99)

add_executable(audisen_debug audisen_sim.c define.h amp.h amp.c ams.h ams.c frame.h frame.c)