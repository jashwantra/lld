#include "vehicle.h"

Vehicle :: Vehicle(const std::string& licenseNumber, VehicleSize size) 
        : licenseNumber(licenseNumber), size(size) {}

std::string Vehicle :: getLicenseNumber() const {
        return licenseNumber;
}

VehicleSize Vehicle :: getSize() const {
        return size;
}


Bike :: Bike(const std::string& licenseNumber) 
        : Vehicle(licenseNumber, VehicleSize::SMALL) {}

Car :: Car(const std::string& licenseNumber) 
        : Vehicle(licenseNumber, VehicleSize::MEDIUM) {}

Truck ::Truck(const std::string& licenseNumber) 
        : Vehicle(licenseNumber, VehicleSize::LARGE) {}