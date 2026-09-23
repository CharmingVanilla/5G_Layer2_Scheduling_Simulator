#pragma once

class UE {
public:
    int id;
    int cqi;

    double totalThroughput;
    double averageThroughput;

    int transmissionCount;
    int failedTransmissionCount;

    UE(int id, int cqi);

    void recordTransmission(double throughput, bool success);
    double calculateBler() const;
    void updateAverageThroughput(double currentThroughput);
};


/*
public:
    int getCqi() const { return cqi; }

    void setCqi(int newCqi) {
        cqi = std::clamp(newCqi, 1, 15);
    }

*/
