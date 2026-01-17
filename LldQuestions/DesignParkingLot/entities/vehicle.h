#ifndef Vehicle_H
#define Vehicle_H 1

#include "enum/vehicleSize.h"
#include <string>
class Vehicle {
protected:
    std::string licenseNumber;
    VehicleSize size;

public:
    Vehicle(const std::string& licenseNumber, VehicleSize size);
    virtual ~Vehicle() = default;
    std::string getLicenseNumber() const ;
    VehicleSize getSize() const ;
};

class Bike : public Vehicle {
public:
    Bike(const std::string& licenseNumber);
};

class Car : public Vehicle {
public:
    Car(const std::string& licenseNumber) ;
};

class Truck : public Vehicle {
public:
    Truck(const std::string& licenseNumber);
};

#endif