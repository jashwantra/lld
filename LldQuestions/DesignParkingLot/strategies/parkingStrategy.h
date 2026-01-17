#ifndef parkingStrategy_H
#define parkingStrategy_H 1

#include <memory>
#include <vector>
#include "entities/parkingSpot.h"
#include "entities/parkingFloor.h"
#include "entities/vehicle.h"

class ParkingStrategy {
public:
    virtual ~ParkingStrategy() = default;
    virtual std::shared_ptr<ParkingSpot> findSpot(const std::vector<std::shared_ptr<ParkingFloor>>& floors, const Vehicle& vehicle) = 0;
};

class NearestFirstStrategy : public ParkingStrategy {
public:
    std::shared_ptr<ParkingSpot> findSpot(const std::vector<std::shared_ptr<ParkingFloor>>& floors, const Vehicle& vehicle) override;
};

class FarthestFirstStrategy : public ParkingStrategy {
public:
    std::shared_ptr<ParkingSpot> findSpot(const std::vector<std::shared_ptr<ParkingFloor>>& floors, const Vehicle& vehicle) override;
};

class BestFitStrategy : public ParkingStrategy {
public:
    std::shared_ptr<ParkingSpot> findSpot(const std::vector<std::shared_ptr<ParkingFloor>>& floors, const Vehicle& vehicle) override ;
};

#endif