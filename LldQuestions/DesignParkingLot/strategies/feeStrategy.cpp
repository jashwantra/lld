#include "feeStrategy.h"

double FlatRateFeeStrategy :: calculateFee(const ParkingTicket& parkingTicket) {
        long long duration = parkingTicket.getExitTimestamp() - parkingTicket.getEntryTimestamp();
        long long hours = (duration / (1000 * 60 * 60)) + 1;
        return hours * RATE_PER_HOUR;
    }


double VehicleBasedFeeStrategy :: calculateFee(const ParkingTicket& parkingTicket) {
        long long duration = parkingTicket.getExitTimestamp() - parkingTicket.getEntryTimestamp();
        long long hours = (duration / (1000 * 60 * 60)) + 1;
        return hours * HOURLY_RATES.at(parkingTicket.getVehicle()->getSize());
    }


const std::map<VehicleSize, double> VehicleBasedFeeStrategy::HOURLY_RATES = {
    {VehicleSize::SMALL, 10.0},
    {VehicleSize::MEDIUM, 20.0},
    {VehicleSize::LARGE, 30.0}
};