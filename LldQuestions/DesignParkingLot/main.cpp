#include "parkingLot.h"
#include <iostream>
#include <iomanip>
using namespace std;
class ParkingLotDemo {
public:
    static void main() {
        auto parkingLot = ParkingLot::getInstance();

        // 1. Initialize the parking lot with floors and spots
        auto floor1 = make_shared<ParkingFloor>(1);
        floor1->addSpot(make_shared<ParkingSpot>("F1-S1", VehicleSize::SMALL));
        floor1->addSpot(make_shared<ParkingSpot>("F1-M1", VehicleSize::MEDIUM));
        floor1->addSpot(make_shared<ParkingSpot>("F1-L1", VehicleSize::LARGE));

        auto floor2 = make_shared<ParkingFloor>(2);
        floor2->addSpot(make_shared<ParkingSpot>("F2-M1", VehicleSize::MEDIUM));
        floor2->addSpot(make_shared<ParkingSpot>("F2-M2", VehicleSize::MEDIUM));

        parkingLot->addFloor(floor1);
        parkingLot->addFloor(floor2);

        parkingLot->setFeeStrategy(make_unique<VehicleBasedFeeStrategy>());

        // 2. Simulate vehicle entries
        cout << "\n--- Vehicle Entries ---" << endl;
        floor1->displayAvailability();
        floor2->displayAvailability();

        auto bike = make_shared<Bike>("B-123");
        auto car = make_shared<Car>("C-456");
        auto truck = make_shared<Truck>("T-789");

        try {
            ParkingTicket* bikeTicket = parkingLot->parkVehicle(bike);
            cout << "Bike parked successfully. Ticket ID: " << bikeTicket->getTicketId() << endl;
            
            ParkingTicket* carTicket = parkingLot->parkVehicle(car);
            cout << "Car parked successfully. Ticket ID: " << carTicket->getTicketId() << endl;
            
            ParkingTicket* truckTicket = parkingLot->parkVehicle(truck);
            cout << "Truck parked successfully. Ticket ID: " << truckTicket->getTicketId() << endl;
        } catch (const exception& e) {
            cout << "Error parking vehicle: " << e.what() << endl;
        }

        cout << "\n--- Availability after parking ---" << endl;
        floor1->displayAvailability();
        floor2->displayAvailability();

        // 3. Simulate another car entry (should go to floor 2)
        auto car2 = make_shared<Car>("C-999");

        try {
            ParkingTicket* car2Ticket = parkingLot->parkVehicle(car2);
            cout << "Second car parked successfully. Ticket ID: " << car2Ticket->getTicketId() << endl;
        } catch (const exception& e) {
            cout << "Error parking second car: " << e.what() << endl;
        }

        // 4. Simulate a vehicle entry that fails (no available spots)
        auto bike2 = make_shared<Bike>("B-000");

        try{
            auto failedBikeTicket = parkingLot->parkVehicle(bike2);
            cout << "failed bike parked successfully. Ticket ID: " << failedBikeTicket->getTicketId() << endl;
        } catch(const exception & e){
            cout << "Error parking failed bike: " << e.what() << endl;
        }

        // 5. Simulate vehicle exits and fee calculation
        cout << "\n--- Vehicle Exits ---" << endl;

        if (car != nullptr) {
            auto fee = parkingLot->unparkVehicle(car->getLicenseNumber());
            if (fee.has_value()) {
                cout << "Car C-456 unparked. Fee: $" << fixed << setprecision(2) << fee.value() << endl;
            }
        }

        cout << "\n--- Availability after one car leaves ---" << endl;
        floor1->displayAvailability();
        floor2->displayAvailability();
    }
};

int main() {
    ParkingLotDemo::main();
    return 0;
}