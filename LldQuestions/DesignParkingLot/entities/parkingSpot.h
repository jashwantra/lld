#ifndef parkingSpot_H
#define parkingSpot_H 1

#include "enum/vehicleSize.h"
#include "vehicle.h"
#include <string>
#include <memory>
#include <mutex>
class ParkingSpot {
private:
    std::string spotId;
    VehicleSize spotSize;
    bool isOccupied;
    std::shared_ptr<Vehicle> parkedVehicle;
    mutable std::mutex spotMutex;

public:
    ParkingSpot(const std::string& spotId, VehicleSize spotSize);

    std::string getSpotId() const ;

    VehicleSize getSpotSize() const ;

    bool isAvailable() const ;

    bool isOccupiedSpot() const ;

    void parkVehicle(std::shared_ptr<Vehicle> vehicle) ;

    void unparkVehicle() ;

    bool canFitVehicle(const Vehicle& vehicle) const ;
};

#endif