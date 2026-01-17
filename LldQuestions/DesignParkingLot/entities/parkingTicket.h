#ifndef parkingTicket_H
#define parkingTicket_H 1

#include <string>
#include <memory>
#include "vehicle.h"
#include "parkingSpot.h"
class ParkingTicket {
private:
    std::string ticketId;
    std::shared_ptr<Vehicle> vehicle;
    std::shared_ptr<ParkingSpot> spot;
    long long entryTimestamp;
    long long exitTimestamp;
    std::string generateUUID() ;

public:
    ParkingTicket(std::shared_ptr<Vehicle> vehicle, std::shared_ptr<ParkingSpot> spot) ;

    std::string getTicketId() const ;
    std::shared_ptr<Vehicle> getVehicle() const ;
    std::shared_ptr<ParkingSpot> getSpot() const ;
    long long getEntryTimestamp() const ;
    long long getExitTimestamp() const ;

    void setExitTimestamp() ;
};

#endif