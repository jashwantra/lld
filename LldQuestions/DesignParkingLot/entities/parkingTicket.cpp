#include "parkingTicket.h"
#include <chrono>

using namespace std;

ParkingTicket :: ParkingTicket(shared_ptr<Vehicle> vehicle, shared_ptr<ParkingSpot> spot) 
        : vehicle(vehicle), spot(spot), exitTimestamp(0) {
        ticketId = generateUUID();
        entryTimestamp = chrono::duration_cast<chrono::milliseconds>(
        chrono::system_clock::now().time_since_epoch()).count();
    }

string ParkingTicket :: generateUUID() {
        srand(time(NULL));
        string uuid = "";
        for (int i = 0; i < 32; i++) {
            uuid += "0123456789abcdef"[rand() % 16];
        }
        return uuid;
    }

std::string ParkingTicket :: getTicketId() const { return ticketId; }

shared_ptr<Vehicle> ParkingTicket :: getVehicle() const { return vehicle; }

shared_ptr<ParkingSpot> ParkingTicket :: getSpot() const { return spot; }

long long ParkingTicket :: getEntryTimestamp() const { return entryTimestamp; }

long long ParkingTicket :: getExitTimestamp() const { return exitTimestamp; }

void ParkingTicket :: setExitTimestamp() {
        exitTimestamp = chrono::duration_cast<chrono::milliseconds>(
            chrono::system_clock::now().time_since_epoch()).count();
    }