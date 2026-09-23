#pragma once
#include "UE.h"
#include "scheduler.h"
#include <vector>

std::vector<UE> runSimulation(
    int numberOfTTIs,
    int allocatedRBs,
    Scheduler& scheduler
);