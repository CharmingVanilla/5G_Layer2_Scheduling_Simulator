#include "Simulation.h"
#include "RadioModel.h"


std::vector<UE> runSimulation(
    int numberOfTTIs,
    int allocatedRBs,
    Scheduler& scheduler
){
std::vector<UE> users;

    users.emplace_back(1, 10);
    users.emplace_back(2, 7);
    users.emplace_back(3, 13);


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