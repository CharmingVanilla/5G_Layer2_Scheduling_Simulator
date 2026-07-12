#include "UE.h"
UE::UE(int id, int cqi)
    :id(id),
    cqi(cqi),
    totalThroughput(0.0),
    averageThroughput(0.0),
    transmissionCount(0),
    failedTransmissionCount(0){

    }

void UE::recordTransmission(double throughput, bool success){

    transmissionCount++;
    if(success){
        totalThroughput += throughput;
    } else {
        failedTransmissionCount++;
    }
}


// const means read the data but not modify it
double UE::calculateBler() const{
    if(transmissionCount == 0){
        return 0.0;
    }

    return static_cast<double>(failedTransmissionCount)/ transmissionCount;
}

void UE::updateAverageThroughput(double currentThroughput){
    const double alpha = 0.1; // smoothing factor for exponential moving average
    averageThroughput = (1-alpha)*averageThroughput+alpha*currentThroughput;
    }