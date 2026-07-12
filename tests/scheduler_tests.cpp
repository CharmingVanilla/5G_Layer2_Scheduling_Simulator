#include <cassert>
#include <iostream>
#include <vector>

#include "UE.h"
#include "RadioModel.h"
#include "RoundRobinScheduler.h"

void testBlerCalculation() {
    UE user(1, 10);

    user.recordTransmission(1000.0, true);
    user.recordTransmission(1000.0, true);
    user.recordTransmission(0.0, false);
    user.recordTransmission(0.0, false);

    assert(user.transmissionCount == 4);
    assert(user.failedTransmissionCount == 2);
    assert(user.calculateBler() == 0.5);

    std::cout << "BLER test passed.\n";
}

void testRoundRobinOrder() {
    std::vector<UE> users;

    users.emplace_back(1, 10);
    users.emplace_back(2, 10);
    users.emplace_back(3, 10);

    RoundRobinScheduler scheduler;

    assert(scheduler.selectUE(users).id == 1);
    assert(scheduler.selectUE(users).id == 2);
    assert(scheduler.selectUE(users).id == 3);
    assert(scheduler.selectUE(users).id == 1);

    std::cout << "Round Robin test passed.\n";
}

void testCqiRange() {
    RadioModel::setSeed(42);

    int cqi = 10;

    for (int i = 0; i < 1000; ++i) {
        RadioModel::updateCqi(cqi);

        assert(cqi >= 1);
        assert(cqi <= 15);
    }

    std::cout << "CQI range test passed.\n";
}

int main() {
    testBlerCalculation();
    testRoundRobinOrder();
    testCqiRange();

    std::cout << "\nAll tests passed!\n";

    return 0;
}