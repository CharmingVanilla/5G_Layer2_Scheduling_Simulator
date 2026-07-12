//do not consider CQI, choose UE in turn
// TTI 0 → UE 1
// TTI 1 → UE 2
// TTI 2 → UE 3
// TTI 3 → UE 1
// TTI 4 → UE 2
#pragma once
#include <vector> //create multiple UE objects
#include "UE.h"

class RoundRobinScheduler {
    public:
    RoundRobinScheduler();

    UE& selectUE(std::vector<UE>& users); //modify the original data not copy

    private:
    int currentIndex; // index of the last scheduled UE
};