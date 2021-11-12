cmake_minimum_required(VERSION 3.20)
project(assignment_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(assignment_1 main.cpp src/Workout.cpp src/Trainer.cpp src/Action.cpp src/Customer.cpp src/Studio.cpp)
