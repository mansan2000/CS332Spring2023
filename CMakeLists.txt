cmake_minimum_required(VERSION 3.23)
project(CS332Spring2023 C)

set(CMAKE_C_STANDARD 11)

include_directories(hw01/asgn2)

#add_executable(CS332Spring2023
##        hw01/asgn2/asgn2.c
##        hw01/asgn2/asgn2.h
#        hw01/emanuels_HW01.c
##        lab01/lab01.c
##        lab02/lab02.c
#        )

add_executable(lab01 lab01/lab01.c)
add_executable(lab03 lab03/lab03.c)
add_executable(emanuels_HW01 hw01/emanuels_HW01.c)