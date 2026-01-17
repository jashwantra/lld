#include "parkingSpot.h"

using namespace std;

ParkingSpot :: ParkingSpot(const string& spotId, VehicleSize spotSize) 
        : spotId(spotId), spotSize(spotSize), isOccupied(false), parkedVehicle(nullptr) {}

string ParkingSpot :: getSpotId() const {
        return spotId;
    }

VehicleSize ParkingSpot :: getSpotSize() const {
        return spotSize;
    }

bool ParkingSpot ::  isAvailable() const {
        lock_guard<mutex> lock(spotMutex);
        return !isOccupied;
    }

bool ParkingSpot :: isOccupiedSpot() const {
        return isOccupied;
    }

void ParkingSpot :: parkVehicle(shared_ptr<Vehicle> vehicle) {
        lock_guard<mutex> lock(spotMutex);
        parkedVehicle = vehicle;
        isOccupied = true;
    }

void ParkingSpot :: unparkVehicle() {
        lock_guard<mutex> lock(spotMutex);
        parkedVehicle = nullptr;
        isOccupied = false;
    }

bool ParkingSpot :: canFitVehicle(const Vehicle& vehicle) const {
        if (isOccupied) return false;

        switch (vehicle.getSize()) {
            case VehicleSize::SMALL:
                return spotSize == VehicleSize::SMALL;
            case VehicleSize::MEDIUM:
                return spotSize == VehicleSize::MEDIUM || spotSize == VehicleSize::LARGE;
            case VehicleSize::LARGE:
                return spotSize == VehicleSize::LARGE;
            default:
                return false;
        }
    }