#include "RadioModel.h"
#include <random>
#include "RadioModel.h"

std::mt19937 RadioModel::generator(42);

void RadioModel::setSeed(unsigned int seed) {
    generator.seed(seed);
}


double RadioModel::cqiToSpectralEfficiency(int cqi){
    static const double efficiencyTable[16]={
        0.0,
        0.1523,
        0.2344,
        0.3770,
        0.6016,
        0.8770,
        1.1758,
        1.4766,
        1.9141,
        2.4063,
        2.7305,
        3.3223,
        3.9023,
        4.5234,
        5.1152,
        5.5547
    };

    if (cqi<1){
        cqi=1;
    }

    if(cqi>15){
        cqi=15;
    }

    return efficiencyTable[cqi];
}

double RadioModel::calculateThroughput(int cqi, int allocateRBs){
    double spectralEfficiency=cqiToSpectralEfficiency(cqi);
    return allocateRBs*spectralEfficiency*180.0; //simplify model
}

double RadioModel::getFailureProbability(int cqi) {
    if (cqi <= 3) {
        return 0.35;
    }

    if (cqi <= 6) {
        return 0.20;
    }

    if (cqi <= 9) {
        return 0.10;
    }

    if (cqi <= 12) {
        return 0.05;
    }

    return 0.02;
}

bool RadioModel::isTransmissionSuccessful(int cqi) {
    double failureProbability =
        getFailureProbability(cqi);

   /*static std::random_device randomDevice; //随机数种子
    static std::mt19937 generator(randomDevice()); //随机生成器 */ 

    std::uniform_real_distribution<double> distribution(
        0.0,
        1.0
    );

    double randomValue = distribution(generator);

    return randomValue >= failureProbability;
}

void RadioModel::updateCqi(int& cqi){
   /*static std::random_device randomDevice;
    static std::mt19937 generator(randomDevice());*/ 

    std::uniform_int_distribution<int> changeDistribution(-1, 1); //-1,0,+1
    int change=changeDistribution(generator);
    cqi+=change;

    if(cqi<1){
        cqi=1;
    }
    if(cqi>15){
        cqi=15;
    }

}