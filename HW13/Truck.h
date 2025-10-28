#pragma once
#include "TransportVehicle.h"

class Truck : public TransportVehicle {
    double loadCapacity;
public:
    Truck() : Truck("Unknown","Unknown",0,0.0,0.0) {}
    Truck(const string& mfr, const string& mdl, int yr, double spd, double load)
        : TransportVehicle(mfr,mdl,yr,spd), loadCapacity(load) {}
    void displayInfo() const override {
        TransportVehicle::displayInfo();
        cout << "Load Capacity: " << loadCapacity << " tons\n";
    }
};
