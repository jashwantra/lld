#include "parkingFloor.h"
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;

ParkingFloor :: ParkingFloor(int floorNumber) : floorNumber(floorNumber) {}

void ParkingFloor ::addSpot(shared_ptr<ParkingSpot> spot) {
        spots[spot->getSpotId()] = spot;
    }

shared_ptr<ParkingSpot> ParkingFloor :: findAvailableSpot(const Vehicle& vehicle) {
        lock_guard<mutex> lock(floorMutex);
        vector<shared_ptr<ParkingSpot>> availableSpots;
        
        for (const auto& pair : spots) {
            auto spot = pair.second;
            if (!spot->isOccupiedSpot() && spot->canFitVehicle(vehicle)) {
                availableSpots.push_back(spot);
            }
        }
        
        if (!availableSpots.empty()) {
            sort(availableSpots.begin(), availableSpots.end(), 
                 [](const shared_ptr<ParkingSpot>& a, const shared_ptr<ParkingSpot>& b) {
                     return static_cast<int>(a->getSpotSize()) < static_cast<int>(b->getSpotSize());
                 });
            return availableSpots[0];
        }
        return nullptr;
    }

void ParkingFloor :: displayAvailability() const {
        std::cout << "--- Floor " << floorNumber << " Availability ---" << endl;
        map<VehicleSize, int> availableCounts;
        
        availableCounts[VehicleSize::SMALL] = 0;
        availableCounts[VehicleSize::MEDIUM] = 0;
        availableCounts[VehicleSize::LARGE] = 0;
        
        for (const auto& pair : spots) {
            auto spot = pair.second;
            if (!spot->isOccupiedSpot()) {
                availableCounts[spot->getSpotSize()]++;
            }
        }

        std::cout << "  SMALL spots: " << availableCounts[VehicleSize::SMALL] << endl;
        std::cout << "  MEDIUM spots: " << availableCounts[VehicleSize::MEDIUM] << endl;
        std::cout << "  LARGE spots: " << availableCounts[VehicleSize::LARGE] << endl;
    }
