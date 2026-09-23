#include "RoundRobinScheduler.h"
#include "RadioModel.h"
#include "Simulation.h"
#include <vector>
#include <stdexcept>
#include <iostream>

void testSimulationTransmissionCount(){
    RoundRobinScheduler scheduler;
    RadioModel::setSeed(42);

    int totalTransmissionCount=0;
    std::vector<UE> users=runSimulation(100, 10, scheduler);
    for(const UE& user:users){
        totalTransmissionCount += user.transmissionCount;
    }

    if(totalTransmissionCount != 100){
        throw std::runtime_error("Total transmission count should be equal to number of TTIs");
    }

}


void testSimulationZero(){
    RoundRobinScheduler scheduler;
    RadioModel::setSeed(42);

    std::vector<UE> users = runSimulation(0,10,scheduler);
    if(users.size() != 3){
        throw std::runtime_error("With zero TTIs, there should still be 3 users in the simulation");
    }

    for(const UE& user:users){
        if(user.transmissionCount != 0){
            throw std::runtime_error("With zero TTIs, transmission count should be zero for all users");
        }

        if(user.failedTransmissionCount != 0){
            throw std::runtime_error("With zero TTIs, failed transmission count should be zero for all users");
        }

        if(user.totalThroughput != 0.0){
            throw std::runtime_error("With zero TTIs, total throughput should be zero for all users");
        }

    }

}

void testRRDistribution(){
    RoundRobinScheduler scheduler;
    RadioModel::setSeed(42);

    std::vector<UE> users= runSimulation(100,10,scheduler);

    if(users.size() != 3){
        throw std::runtime_error("There should be 3 users in the simulation");
    }
    if(users[0].transmissionCount !=34 ){
        throw std::runtime_error("UE 1 should have 34 transmissions in 100 TTIs with Round Robin scheduling");
    }

    if(users[1].transmissionCount != 33){
        throw std::runtime_error("UE 2 should have 33 transmissions in 100 TTIs with Round Robin scheduling");
    }
    if(users[2].transmissionCount != 33){
        throw std::runtime_error("UE 3 should have 33 transmissions in 100 TTIs with Round Robin scheduling");
    }

}


int main() {
    testSimulationTransmissionCount();
    testSimulationZero();
    testRRDistribution();
    std::cout << "Simulation transmission count test passed.\n";
    return 0;
}