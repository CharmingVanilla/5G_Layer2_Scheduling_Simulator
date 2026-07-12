#include "ProportionalFairScheduler.h"
#include "RadioModel.h"

#include <limits>
#include <stdexcept>

UE& ProportionalFairScheduler::selectUE(std::vector<UE>& users) {
    if (users.empty()) {
        throw std::runtime_error(
            "Cannot schedule an empty UE list."
        );
    }

    int bestIndex = 0;

    double bestMetric =
        -std::numeric_limits<double>::infinity(); //initialization to negative infinity

    for (int i = 0; i < static_cast<int>(users.size()); ++i) {
        double estimatedRate =
            RadioModel::calculateThroughput(
                users[i].cqi,
                10
            );

        double denominator =
            users[i].averageThroughput;

        if (denominator < 0.001) {
            denominator = 0.001;
        }

        double metric =
            estimatedRate / denominator; ////equation

        if (metric > bestMetric) {
            bestMetric = metric;
            bestIndex = i;
        }
    }

    return users[bestIndex];
}