cmake_minimum_required(VERSION 3.16)

project(5GLayer2Scheduler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(
    L2_simulator
    src/Simulation.cpp
    src/main.cpp
    src/UE.cpp
    src/RadioModel.cpp
    src/RoundRobinScheduler.cpp
    src/ProportionalFairScheduler.cpp
)


add_executable(
    scheduler_tests
    tests/scheduler_tests.cpp
    src/UE.cpp
    src/RadioModel.cpp
    src/RoundRobinScheduler.cpp
    src/ProportionalFairScheduler.cpp
)

add_executable(
    simulation_tests
    tests/simulation_tests.cpp
    src/Simulation.cpp
    src/UE.cpp
    src/RadioModel.cpp
    src/RoundRobinScheduler.cpp
    src/ProportionalFairScheduler.cpp
)


add_executable(
    ue_tests
    tests/ue_tests.cpp
    src/UE.cpp
)

enable_testing()
add_test(NAME ue_tests COMMAND ue_tests)
add_test(NAME simulation_tests COMMAND simulation_tests)
add_test(NAME scheduler_tests COMMAND scheduler_tests)