#pragma once

#include <vector>
#include "UE.h"
#include "scheduler.h"

class ProportionalFairScheduler :public Scheduler{
public:
    UE& selectUE(std::vector<UE>& users) override;
};