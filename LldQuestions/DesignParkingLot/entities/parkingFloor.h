#ifndef parkingFloor_H
#define parkingFloor_H 1

#include <unordered_map>
#include <mutex>
#include <memory>
#include "parkingSpot.h"
#include "vehicle.h"
class ParkingFloor {
private:
    int floorNumber;
    std::unordered_map<std::string, std::shared_ptr<ParkingSpot>> spots;
    mutable std::mutex floorMutex;

public:
    ParkingFloor(int floorNumber);

    void addSpot(std::shared_ptr<ParkingSpot> spot) ;

    std::shared_ptr<ParkingSpot> findAvailableSpot(const Vehicle& vehicle) ;

    void displayAvailability() const ;
};

#endif