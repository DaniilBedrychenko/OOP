#pragma once
#include "TransportVehicle.h"

class Ship : public TransportVehicle {
    double displacement;
public:
    Ship() : Ship("Unknown","Unknown",0,0.0,0.0) {}
    Ship(const string& mfr, const string& mdl, int yr, double spd, double disp)
        : TransportVehicle(mfr,mdl,yr,spd), displacement(disp) {}
    void displayInfo() const override {
        TransportVehicle::displayInfo();
        cout << "Displacement: " << displacement << " tons\n";
    }
};
