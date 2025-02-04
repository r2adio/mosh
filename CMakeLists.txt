cmake_minimum_required(VERSION 3.13)

# Set the project name
project(mosh)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable
add_executable(mosh src/main.cpp)
