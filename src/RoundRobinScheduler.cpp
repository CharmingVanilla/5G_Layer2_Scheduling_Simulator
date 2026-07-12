#include "RoundRobinScheduler.h"
#include <stdexcept> // for std::runtime_error

RoundRobinScheduler::RoundRobinScheduler()
    : currentIndex(0) // starts with index 0
    {}

UE& RoundRobinScheduler::selectUE(std::vector<UE>& users) {
    if (users.empty()) {
        throw std::runtime_error("Can not schedule a empty user list.");
    }

    UE& selectedUE=users[currentIndex];

    currentIndex = (currentIndex + 1) % users.size(); // Move to the next index, wrap around if needed
    return selectedUE;
}
