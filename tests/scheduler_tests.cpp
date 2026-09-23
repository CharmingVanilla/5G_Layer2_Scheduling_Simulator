#include <iostream>
#include <vector>

#include "UE.h"
#include "RadioModel.h"
#include "RoundRobinScheduler.h"
#include "ProportionalFairScheduler.h"
#include <stdexcept>

void testCqiRange() {
    RadioModel::setSeed(42);

    int cqi = 10;

    for (int i = 0; i < 1000; ++i) {
        RadioModel::updateCqi(cqi);

        if(cqi<1 || cqi>15){
            throw std::runtime_error("CQI should always be in the range [1, 15]");
        }
    }

    std::cout << "CQI range test passed.\n";
}

//RoundRobin Tests
void testRoundRobinOrder() {
 
    std::vector<UE> users;

    users.emplace_back(1,10);
    users.emplace_back(2,10);
    users.emplace_back(3,10);

    RoundRobinScheduler scheduler{};
    
    if(scheduler.selectUE(users).id != 1){
        throw std::runtime_error("First selected UE should be UE 1");
    }
    
    if(scheduler.selectUE(users).id != 2){
        throw std::runtime_error("Second selected UE should be UE 2");
    }

    if(scheduler.selectUE(users).id != 3){
        throw std::runtime_error("Third selected UE should be UE 3");
    }

    if(scheduler.selectUE(users).id != 1){
        throw std::runtime_error("Fourth selected UE should be UE 1");
    }

    std::cout << "Round-robin order test passed.\n";

}

void testRoundRobinEmptyList(){

    std::vector<UE> users;
    RoundRobinScheduler scheduler{};

    bool exceptionCaught = false;

    try{
        scheduler.selectUE(users);

    }catch(const std::runtime_error& error){
        exceptionCaught = true; //Confirm the expected exception was thrown
    }

    if(exceptionCaught == false){
        throw std::runtime_error("Selecting from an empty list should throw an exception"); 
    }
}

void testRoundRobinSingleUser(){
    std::vector<UE> users;
    users.emplace_back(7,10);

    RoundRobinScheduler scheduler{};
    for(int i=0; i<5 ;i++){
        if(scheduler.selectUE(users).id != 7){
            throw std::runtime_error("With a single user, the selected UE should always be UE 7");
        }
    }

}

// Proportional Fair Tests

void testPFselection(){
    // same avergae throughput, different CQI
    std::vector<UE> users;
    users.emplace_back(1,5);
    users.emplace_back(2,15);

    users[0].averageThroughput=100.0; 
    users[1].averageThroughput=100.0; 

    ProportionalFairScheduler scheduler{};
    if(scheduler.selectUE(users).id != 2){
        throw std::runtime_error("With same average throughput, the UE with higher CQI should be selected");
    }
}

void testPFUsesHistory(){
    //same cqi different average throughput
    std::vector<UE> users;
    users.emplace_back(1,10);
    users.emplace_back(2,10);

    users[0].averageThroughput=100.0;
    users[1].averageThroughput=200.0;

    ProportionalFairScheduler scheduler{};
    if(scheduler.selectUE(users).id != 1){
        throw std::runtime_error("With same CQI, the UE with lower average throughput should be selected");
    }

}

void testRFWithZeroHistory(){
    std::vector<UE> users;
    users.emplace_back(1,5);
    users.emplace_back(2,15);

    ProportionalFairScheduler scheduler{};
    if(scheduler.selectUE(users).id != 2){
        throw std::runtime_error("With zero average throughput, the UE with higher CQI should be selected");
    }

}

void testPFTieBreaking(){
    std::vector<UE> users;
    users.emplace_back(1,10);
    users.emplace_back(2,10);

    users[0].averageThroughput=100;
    users[1].averageThroughput=100;

    ProportionalFairScheduler scheduler{};
    if(scheduler.selectUE(users).id!=1){
        throw std::runtime_error("With same CQI and same average throughput, the first UE should be selected");
    }

}

void testPFEmptyList(){
    std::vector<UE> users;
    ProportionalFairScheduler scheduler{};

    bool exceptionCaught = false;

    try{
        scheduler.selectUE(users);

    }catch(const std::runtime_error& error){
        exceptionCaught = true; //Confirm the expected exception was thrown
    }

    if(exceptionCaught == false){
        throw std::runtime_error("Selecting from an empty list should throw an exception"); 
    }
}

void testSchedulerPolymorphism(){
    std::vector<UE> users;
    users.emplace_back(1,5);
    users.emplace_back(2,15);

    RoundRobinScheduler rr{};
    Scheduler& scheduler= rr; // Polymorphic behavior
    if(scheduler.selectUE(users).id != 1){
        throw std::runtime_error("Polymorphic call to RoundRobinScheduler failed");
    }

    ProportionalFairScheduler pf{};
    Scheduler& scheduler2= pf; // Polymorphic behavior
    if(scheduler2.selectUE(users).id != 2){
        throw std::runtime_error("Polymorphic call to ProportionalFairScheduler failed");
    }
}



int main() {
    testRoundRobinOrder();
    testRoundRobinEmptyList();
    testRoundRobinSingleUser();
    testCqiRange();
    testPFselection();
    testPFUsesHistory();
    testRFWithZeroHistory();
    testPFTieBreaking();
    testPFEmptyList();
    testSchedulerPolymorphism();
    std::cout << "\nAll tests passed!\n";

    return 0;
}