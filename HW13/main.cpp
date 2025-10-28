#include "Bicycle.h"
#include "Truck.h"
#include "Airplane.h"
#include "Ship.h"

int main() {
    Bicycle bike("Giant","Defy Advanced",2023,45.0,true);
    cout << "=== Bicycle ===\n";
    bike.displayInfo();
    cout << '\n';

    Truck truck("MAN","TGX",2024,90.0,44.0);
    cout << "=== Truck ===\n";
    truck.displayInfo();
    cout << '\n';

    Airplane plane("Airbus","A380",2020,1020.0,43000);
    cout << "=== Airplane ===\n";
    plane.displayInfo();
    cout << '\n';

    Ship ship("Hyundai","Iconic",2022,23.0,200000.0);
    cout << "=== Ship ===\n";
    ship.displayInfo();

    return 0;
}
