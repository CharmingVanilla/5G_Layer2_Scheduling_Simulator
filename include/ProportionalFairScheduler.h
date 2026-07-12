#pragma once

#include <vector>
#include "UE.h"

class ProportionalFairScheduler {
public:
    UE& selectUE(std::vector<UE>& users);
};