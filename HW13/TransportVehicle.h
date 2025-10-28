#pragma once
#include <iostream>

using namespace std;

class TransportVehicle {
protected:
    string manufacturer;
    string model;
    int year;
    double maxSpeed;
public:
    TransportVehicle() : TransportVehicle("Unknown","Unknown",0,0.0) {}
    TransportVehicle(const string& mfr, const string& mdl, int yr, double spd)
        : manufacturer(mfr), model(mdl), year(yr), maxSpeed(spd) {}
    virtual void displayInfo() const {
        cout << "Manufacturer: " << manufacturer << '\n';
        cout << "Model: " << model << '\n';
        cout << "Year: " << year << '\n';
        cout << "Max Speed: " << maxSpeed << " km/h\n";
    }
    virtual ~TransportVehicle() = default;
};
