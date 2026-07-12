#include <iostream>
#include <vector>
#include "UE.h"
#include "RoundRobinScheduler.h"
#include "RadioModel.h"
#include "ProportionalFairScheduler.h"
#include <string>


double calculateJainFairness(const std::vector<UE>& users) {
    double sum = 0.0;
    double squareSum = 0.0;

    for (const UE& user : users) {
        sum += user.totalThroughput;
        squareSum += user.totalThroughput * user.totalThroughput;
    }

    if (squareSum == 0.0) {
        return 0.0;
    }

    return (sum * sum) /
           (users.size() * squareSum);
} //closer to 1 more fair


void printResults(
    const std::string& schedulerName,
    const std::vector<UE>& users
) {
    double totalSystemThroughput = 0.0;
    int totalTransmissions = 0;
    int totalFailures = 0;

    std::cout
        << "\n===== "
        << schedulerName
        << " Results =====\n";

    for (const UE& user : users) {
        totalSystemThroughput += user.totalThroughput;
        totalTransmissions += user.transmissionCount;
        totalFailures += user.failedTransmissionCount;

        std::cout
            << "UE " << user.id
            << " | CQI: " << user.cqi
            << " | Scheduling Count: "
            << user.transmissionCount
            << " | Throughput: "
            << user.totalThroughput
            << " | BLER: "
            << user.calculateBler() * 100.0
            << "%\n";
    }

    double averageBler = 0.0;

    if (totalTransmissions > 0) {
        averageBler =
            static_cast<double>(totalFailures)
            / totalTransmissions;
    }

    std::cout
        << "Total System Throughput: "
        << totalSystemThroughput
        << "\nAverage BLER: "
        << averageBler * 100.0
        << "%"
        << "\nJain Fairness Index: "
        << calculateJainFairness(users)
        << "\n";
}


std::vector<UE> runRoundRobinSimulation(
    int numberOfTTIs,
    int allocatedRBs
) {
    std::vector<UE> users;

    users.emplace_back(1, 10);
    users.emplace_back(2, 7);
    users.emplace_back(3, 13);

    RoundRobinScheduler scheduler;

    for (int tti = 0; tti < numberOfTTIs; ++tti) {
        for (UE& user : users) {
            RadioModel::updateCqi(user.cqi);
        }

        UE& selectedUE =
            scheduler.selectUE(users);

        double estimatedThroughput =
            RadioModel::calculateThroughput(
                selectedUE.cqi,
                allocatedRBs
            );

        bool success =
            RadioModel::isTransmissionSuccessful(
                selectedUE.cqi
            );

        double deliveredThroughput =
            success ? estimatedThroughput : 0.0;

        for (UE& user : users) {
            if (user.id == selectedUE.id) {
                user.updateAverageThroughput(
                    deliveredThroughput
                );
            } else {
                user.updateAverageThroughput(0.0);
            }
        }

        selectedUE.recordTransmission(
            deliveredThroughput,
            success
        );
    }

    return users;
}


std::vector<UE> runProportionalFairSimulation(
    int numberOfTTIs,
    int allocatedRBs
) {
    std::vector<UE> users;

    users.emplace_back(1, 10);
    users.emplace_back(2, 7);
    users.emplace_back(3, 13);

    ProportionalFairScheduler scheduler;

    for (int tti = 0; tti < numberOfTTIs; ++tti) {
        for (UE& user : users) {
            RadioModel::updateCqi(user.cqi);
        }

        UE& selectedUE =
            scheduler.selectUE(users);

        double estimatedThroughput =
            RadioModel::calculateThroughput(
                selectedUE.cqi,
                allocatedRBs
            );

        bool success =
            RadioModel::isTransmissionSuccessful(
                selectedUE.cqi
            );

        double deliveredThroughput =
            success ? estimatedThroughput : 0.0;

        for (UE& user : users) {
            if (user.id == selectedUE.id) {
                user.updateAverageThroughput(
                    deliveredThroughput
                );
            } else {
                user.updateAverageThroughput(0.0);
            }
        }

        selectedUE.recordTransmission(
            deliveredThroughput,
            success
        );
    }

    return users;
}


int main() {
    const int numberOfTTIs = 1000;
    const int allocatedRBs = 10;

    RadioModel::setSeed(42);
    std::vector<UE> roundRobinUsers =
        runRoundRobinSimulation(
            numberOfTTIs,
            allocatedRBs
        );

    RadioModel::setSeed(42);
    std::vector<UE> proportionalFairUsers =
        runProportionalFairSimulation(
            numberOfTTIs,
            allocatedRBs
        );

    printResults(
        "Round Robin",
        roundRobinUsers
    );

    printResults(
        "Proportional Fair",
        proportionalFairUsers
    );

    return 0;
}