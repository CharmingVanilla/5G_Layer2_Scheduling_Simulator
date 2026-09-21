//UE: initialization, statistics and average throughput calculation
#include "UE.h"
#include <stdexcept>
#include <iostream>
#include <cmath>

void testUEInitialState(){
    UE user(1,10);

    if(user.id != 1){// test：id=2
        throw std::runtime_error("Incorrect UE ID");
    }

    if(user.cqi != 10){
        throw std::runtime_error("Incorrect UE CQI");
    }

    if(user.totalThroughput != 0.0){
        throw std::runtime_error("new UE should have 0.0 throughput");
    }

    if(user.transmissionCount != 0){
        throw std::runtime_error("new UE should have 0 transmission count");
    }
}

void testSuccessfulTransmission(){
    UE user(1,10);
    user.recordTransmission(1000.0, true);
    if(user.totalThroughput != 1000.0){
        throw std::runtime_error("Total throughput should be 1000.0 after one successful transmission");
    }

    if(user.transmissionCount != 1){
        throw std::runtime_error("Transmission count should be 1 after one successful transmission");
    }
    
    if(user.failedTransmissionCount != 0){
        throw std::runtime_error("Failed transmission count should be 0 after one successful transmission");
    }
}

void testFailedTransmission(){
    UE user(1,10);
    user.recordTransmission(1000.0, false);
    if(user.totalThroughput != 0.0){
        throw std::runtime_error("Total throughput should be 0.0 after one failed transmission");
    }

    if(user.transmissionCount != 1){
        throw std::runtime_error("Transmission count should be 1 after one failed transmission");
    }
    
    if(user.failedTransmissionCount != 1){
        throw std::runtime_error("Failed transmission count should be 1 after one failed transmission");
    }    
}

void testBlerCalculation(){
    UE user(1,10);
    user.recordTransmission(1000.0, true);
    user.recordTransmission(500.0, true);
    user.recordTransmission(800.0, false);
    user.recordTransmission(200.0, false);

    if(user.totalThroughput != 1500.0){
        throw std::runtime_error("Total throughput should be 1500.0 after two successful transmissions");
    }
    
    if(user.transmissionCount !=4 ){
        throw std::runtime_error("Transmission count should be 4 after four transmissions");
    }

    if(user.failedTransmissionCount != 2){
        throw std::runtime_error("Failed transmission count should be 2 after two failed transmissions");
    }

    if(user.calculateBler() != 0.5){
        throw std::runtime_error("BLER should be 0.5 after two failed transmissions out of four");
    }
    
}

void testBlerWithoutTransmission(){
    UE user(1,10);

    if(user.calculateBler() != 0.0){
        throw std::runtime_error("BLER should be 0.0 when there are no transmissions");
    }

}

void testAverageThroughput(){
    UE user(1,10);
    user.updateAverageThroughput(100.0);
    
    double expectedAverage_0 = 10.0;
    if(!std::isfinite(user.averageThroughput) || std::abs(user.averageThroughput - expectedAverage_0) > 1e-9){
        throw std::runtime_error("Average throughput calculation is incorrect");
    }

    user.updateAverageThroughput(100.0);
    double expectedAverage_1 = 19.0;
    if(!std::isfinite(user.averageThroughput) || std::abs(user.averageThroughput - expectedAverage_1) > 1e-9){
        throw std::runtime_error("Average throughput calculation is incorrect");
    }


    user.updateAverageThroughput(0.0);
    double expectedAverage_2 = 17.1;
    if(!std::isfinite(user.averageThroughput) || std::abs(user.averageThroughput - expectedAverage_2) > 1e-9){
        throw std::runtime_error("Average throughput calculation is incorrect");
    }

}

int main(){

    testUEInitialState();
    std::cout << "UE initialization test passed.\n";
    testSuccessfulTransmission();
    std::cout << "UE successful transmission test passed.\n";
    testFailedTransmission();
    std::cout << "UE failed transmission test passed.\n";
    testBlerCalculation();
    std::cout << "UE BLER calculation test passed.\n";
    testBlerWithoutTransmission();
    std::cout << "UE BLER without transmission test passed.\n";
    testAverageThroughput();
    std::cout << "UE average throughput test passed.\n";
    return 0;
}