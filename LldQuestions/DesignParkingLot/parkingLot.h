#ifndef parkingLot_H
#define parkingLot_H 1

#include "entities/parkingFloor.h"
#include "entities/parkingTicket.h"
#include "strategies/feeStrategy.h"
#include <map>
#include <string>
#include <vector>
#include <optional>
#include <memory>
class ParkingLot {
private:
    static ParkingLot* instance;
    std::vector<std::shared_ptr<ParkingFloor>> floors;
    std::map<std::string, ParkingTicket*> activeTickets;
    std::unique_ptr<FeeStrategy> feeStrategy;

    ParkingLot();

public:
    static ParkingLot* getInstance();

    void addFloor(std::shared_ptr<ParkingFloor> floor);

    void setFeeStrategy(std::unique_ptr<FeeStrategy> feeStrategy) ;

    ParkingTicket* parkVehicle(std::shared_ptr<Vehicle> vehicle) ;

    std::optional<double> unparkVehicle(const std::string& license) ;
};

#endif