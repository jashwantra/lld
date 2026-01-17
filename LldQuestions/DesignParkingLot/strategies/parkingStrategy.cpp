#include "parkingStrategy.h"

using namespace std;

shared_ptr<ParkingSpot> NearestFirstStrategy ::
    findSpot(const vector<shared_ptr<ParkingFloor>>& floors, const Vehicle& vehicle) {
        for (const auto& floor : floors) {
            auto spot = floor->findAvailableSpot(vehicle);
            if (spot != nullptr) {
                return spot;
            }
        }
        return nullptr;
    }


shared_ptr<ParkingSpot> FarthestFirstStrategy ::
    findSpot(const vector<shared_ptr<ParkingFloor>>& floors, const Vehicle& vehicle) {
        vector<shared_ptr<ParkingFloor>> reversedFloors(floors.rbegin(), floors.rend());
        for (const auto& floor : reversedFloors) {
            auto spot = floor->findAvailableSpot(vehicle);
            if (spot != nullptr) {
                return spot;
            }
        }
        return nullptr;
    }

shared_ptr<ParkingSpot> BestFitStrategy ::
    findSpot(const vector<shared_ptr<ParkingFloor>>& floors, const Vehicle& vehicle) {
        shared_ptr<ParkingSpot> bestSpot = nullptr;

        for (const auto& floor : floors) {
            auto spotOnThisFloor = floor->findAvailableSpot(vehicle);

            if (spotOnThisFloor != nullptr) {
                if (bestSpot == nullptr) {
                    bestSpot = spotOnThisFloor;
                } else {
                    if (static_cast<int>(spotOnThisFloor->getSpotSize()) < static_cast<int>(bestSpot->getSpotSize())) {
                        bestSpot = spotOnThisFloor;
                    }
                }
            }
        }
        return bestSpot;
    }
