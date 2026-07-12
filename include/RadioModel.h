#pragma once
#include <random>
class RadioModel{
    public: 
    static double cqiToSpectralEfficiency(int cqi);
    static double calculateThroughput(int cqi, int allocateRBs);

    static double getFailureProbability(int cqi);
    static bool isTransmissionSuccessful(int cqi);
    static void updateCqi(int& cqi);
    static void setSeed(unsigned int seed);

    private:
    static std::mt19937 generator;
};
