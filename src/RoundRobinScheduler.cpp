#include "RoundRobinScheduler.h"
#include <stdexcept> // for std::runtime_error

RoundRobinScheduler::RoundRobinScheduler()
    : currentIndex(0) // starts with index 0
    {}

UE& RoundRobinScheduler::selectUE(std::vector<UE>& users) {
    //RoundRobinScheduler 有一个叫 selectUE 的函数。
    //它接收“一组 UE”，然后从里面返回“某一个 UE”。
    //而且输入和返回都不是复制品，而是原来的对象。
    if (users.empty()) {
        throw std::runtime_error("Can not schedule a empty user list.");
    }

    UE& selectedUE=users[currentIndex];

    currentIndex = (currentIndex + 1) % users.size(); // 走到最后一个 UE 后，重新回到第一个 UE。
    return selectedUE;
}
