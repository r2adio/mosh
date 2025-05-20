cmake_minimum_required(VERSION 3.13)

# Set the project name
project(mosh C)

# Specify the C standard
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add the executable
add_executable(mosh src/main.c)
