#pragma once
#include "TransportVehicle.h"

class Airplane : public TransportVehicle {
    int maxAltitude;
public:
    Airplane() : Airplane("Unknown","Unknown",0,0.0,0) {}
    Airplane(const string& mfr, const string& mdl, int yr, double spd, int alt)
        : TransportVehicle(mfr,mdl,yr,spd), maxAltitude(alt) {}
    void displayInfo() const override {
        TransportVehicle::displayInfo();
        cout << "Max Altitude: " << maxAltitude << " feet\n";
    }
};
