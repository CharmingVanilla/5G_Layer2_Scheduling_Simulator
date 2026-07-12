cmake_minimum_required(VERSION 3.16)

project(5GLayer2Scheduler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(
    scheduler_tests
    tests/scheduler_tests.cpp
    src/UE.cpp
    src/RadioModel.cpp
    src/RoundRobinScheduler.cpp
)