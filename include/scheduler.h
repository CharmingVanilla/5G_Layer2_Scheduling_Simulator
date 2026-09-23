#pragma once
#include <vector>
#include "UE.h"


class Scheduler{
public:
    virtual UE& selectUE(std::vector<UE>& users) = 0; //pure virtual
    virtual ~Scheduler() = default; //destructor
};