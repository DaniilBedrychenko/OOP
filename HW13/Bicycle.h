#pragma once
#include "TransportVehicle.h"

class Bicycle : public TransportVehicle {
    bool hasGears;
public:
    Bicycle() : Bicycle("Unknown","Unknown",0,0.0,false) {}
    Bicycle(const string& mfr, const string& mdl, int yr, double spd, bool gears)
        : TransportVehicle(mfr,mdl,yr,spd), hasGears(gears) {}
    void displayInfo() const override {
        TransportVehicle::displayInfo();
        cout << "Has Gears: " << (hasGears ? "Yes" : "No") << '\n';
    }
};
