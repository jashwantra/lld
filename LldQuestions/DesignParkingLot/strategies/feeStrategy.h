#ifndef feeStrategy_H
#define feeStrategy_H 1

#include "entities/parkingTicket.h"
#include <map>
class FeeStrategy {
public:
    virtual ~FeeStrategy() = default;
    virtual double calculateFee(const ParkingTicket& parkingTicket) = 0;
};

class FlatRateFeeStrategy : public FeeStrategy {
private:
    static constexpr double RATE_PER_HOUR = 10.0;

public:
    double calculateFee(const ParkingTicket& parkingTicket) override ;
};

class VehicleBasedFeeStrategy : public FeeStrategy {
private:
    static const std::map<VehicleSize, double> HOURLY_RATES;

public:
    double calculateFee(const ParkingTicket& parkingTicket) override ;
};

#endif