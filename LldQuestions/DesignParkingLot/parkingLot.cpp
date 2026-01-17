#include "parkingLot.h"
#include <stdexcept>

using namespace std;

ParkingLot* ParkingLot::instance = NULL;
ParkingLot :: ParkingLot() :feeStrategy(make_unique<VehicleBasedFeeStrategy>()){
}

ParkingLot * ParkingLot :: getInstance() {
        if (instance == NULL) {
            instance = new ParkingLot();
        }
        return instance;
    }

void ParkingLot :: addFloor(shared_ptr<ParkingFloor> floor) {
        floors.push_back(floor);
    }

void ParkingLot :: setFeeStrategy(unique_ptr<FeeStrategy> feeStrategy) {
        this->feeStrategy = move(feeStrategy);
    }

ParkingTicket* ParkingLot :: parkVehicle(shared_ptr<Vehicle> vehicle) {
        for (int i = 0; i < floors.size(); i++) {
            shared_ptr<ParkingSpot> spot = floors[i]->findAvailableSpot(*vehicle);
            if (spot != NULL) {
                spot->parkVehicle(vehicle);
                ParkingTicket* ticket = new ParkingTicket(vehicle, spot);
                activeTickets[vehicle->getLicenseNumber()] = ticket;
                return ticket;
            }
        }
        throw runtime_error("No available spot for vehicle");
    }

optional<double> ParkingLot :: unparkVehicle(const string& license) {
        map<string, ParkingTicket*>::iterator it = activeTickets.find(license);
        if (it == activeTickets.end()) {
            throw runtime_error("Ticket not found");
        }

        ParkingTicket* ticket = it->second;
        activeTickets.erase(it);

        ticket->getSpot()->unparkVehicle();
        ticket->setExitTimestamp();
        double fee = feeStrategy->calculateFee(*ticket);
        
        delete ticket;
        return fee;
    }

