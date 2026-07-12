# 5G Layer 2 Scheduling Simulator

A lightweight C++17 simulator for comparing scheduling strategies in a simplified 5G Layer 2 radio environment.

The project implements Round Robin (RR) and Proportional Fair (PF) scheduling, dynamic CQI variation, CQI-based throughput estimation, transmission failure simulation, BLER measurement, and fairness evaluation.

## Project Motivation

Scheduling is an important function in the Radio Access Network (RAN), where limited radio resources must be allocated efficiently among multiple User Equipments (UEs).

This project was developed to explore C++ software design and fundamental radio resource scheduling concepts through a simplified simulation environment.

The simulator compares two scheduling strategies:

- Round Robin (RR)
- Proportional Fair (PF)

Their performance is evaluated using system throughput, Block Error Rate (BLER), per-UE throughput, and Jain's Fairness Index.

## Features

- Object-oriented C++17 implementation
- Multi-UE simulation
- Round Robin scheduling
- Proportional Fair scheduling
- Dynamic CQI variation
- CQI-to-spectral-efficiency mapping
- Simplified throughput estimation
- CQI-dependent transmission failure simulation
- BLER calculation
- Exponential moving average throughput tracking
- Jain's Fairness Index calculation
- Fixed random seed for reproducible simulations
- CMake-based build system

## Project Structure

    cpp-5g-l2-scheduler/
    ├── CMakeLists.txt
    ├── README.md
    ├── include/
    │   ├── UE.h
    │   ├── RadioModel.h
    │   ├── RoundRobinScheduler.h
    │   └── ProportionalFairScheduler.h
    └── src/
        ├── main.cpp
        ├── UE.cpp
        ├── RadioModel.cpp
        ├── RoundRobinScheduler.cpp
        └── ProportionalFairScheduler.cpp

## Architecture

The simulator separates UE state management, radio modeling, and scheduling logic into independent components.

### UE

The `UE` class maintains the state and transmission statistics of each simulated user.

It stores:

- UE ID
- CQI
- Total throughput
- Average throughput
- Transmission count
- Failed transmission count

It also provides functions for recording transmission results, updating average throughput, and calculating BLER.

### RadioModel

The `RadioModel` class provides simplified radio environment modeling.

Its responsibilities include:

- Mapping CQI to spectral efficiency
- Estimating achievable throughput
- Simulating CQI variation
- Modeling CQI-dependent transmission failures
- Managing seeded random number generation

### RoundRobinScheduler

The Round Robin scheduler selects UEs sequentially without considering channel quality.

For example:

    UE1 -> UE2 -> UE3 -> UE1 -> UE2 -> UE3

This strategy provides similar scheduling opportunities to all UEs but does not take advantage of favorable channel conditions.

### ProportionalFairScheduler

The Proportional Fair scheduler selects the UE with the highest PF metric:

    PF Metric = Estimated Rate / Historical Average Throughput

This approach balances system throughput and fairness.

UEs with favorable current channel conditions receive a higher estimated rate, while UEs that have received less throughput in the past receive higher scheduling priority.

## Simulation Flow

For every Transmission Time Interval (TTI), the simulator performs the following steps:

    Update CQI for all UEs
            |
            v
    Select UE using scheduler
            |
            v
    Estimate achievable throughput
            |
            v
    Simulate transmission success or failure
            |
            v
    Update average throughput
            |
            v
    Record transmission statistics

The simulation is executed separately for Round Robin and Proportional Fair scheduling.

## Performance Metrics

The following metrics are used to compare the scheduling strategies.

### Total System Throughput

The sum of successfully delivered throughput across all UEs.

### Block Error Rate (BLER)

Calculated as:

    BLER = Failed Transmissions / Total Transmissions

### Per-UE Throughput

The total successfully delivered throughput for each UE.

### Jain's Fairness Index

Calculated as:

    J = (sum(x_i))^2 / (n * sum(x_i^2))

where `x_i` represents the throughput achieved by each UE.

A value closer to `1.0` indicates a more balanced throughput distribution.

## Build

The project requires:

- C++17 compatible compiler
- CMake 3.16 or newer

Clone the repository and create a build directory:

    mkdir build
    cd build

Configure the project:

    cmake ..

Build the executable:

    cmake --build .

Run the simulator:

    ./scheduler

## Example Results

A reproducible simulation was conducted with three UEs over 1,000 TTIs using a fixed random seed.

    ===== Round Robin Results =====

    Total System Throughput: 2.43612e+06
    Average BLER: 19.8%
    Jain Fairness Index: 0.938715

    ===== Proportional Fair Results =====

    Total System Throughput: 2.58328e+06
    Average BLER: 17.7%
    Jain Fairness Index: 0.950008

Under the simulated scenario, Proportional Fair scheduling achieved approximately 6.0% higher total system throughput compared with Round Robin scheduling.

The average BLER decreased from 19.8% to 17.7%, while the Jain's Fairness Index increased from 0.939 to 0.950.

These results demonstrate how Proportional Fair scheduling can balance system throughput and fairness by considering both current channel conditions and historical average throughput.

A fixed random seed is used to ensure reproducible simulation results.

## Limitations

This project is a simplified educational simulator and does not implement a complete 3GPP NR Layer 2 scheduler.

Simplifications include:

- Abstracted resource block allocation
- Simplified CQI-to-throughput mapping
- Simplified channel variation model
- Simplified transmission failure probability model
- No HARQ process modeling
- No MCS selection
- No QoS-aware scheduling
- No multi-cell interference modeling

## Future Improvements

Possible future extensions include:

- Configurable number of UEs
- Multiple traffic models
- HARQ retransmission simulation
- MCS selection
- QoS-aware scheduling
- Additional scheduling algorithms
- CSV result export
- Automated unit testing
- Performance visualization

## Technologies

- C++17
- CMake
- Object-Oriented Programming
- STL containers
- Random number generation
- Radio resource scheduling concepts

## Author

Hongyan Li