// Practical 08: Factory Design Pattern
// A FACTORY function creates the right kind of object based on a requested
// type. The caller does not use "new Car" or "new Bike" directly; it only
// asks the factory and uses the result through the Vehicle interface.
//
// Why Factory fits here: the program decides at RUNTIME which vehicle to
// create (for example from user input), and the calling code should not
// need to know about every concrete class.
//
//   main() --asks--> VehicleFactory::create("car")  --returns--> Vehicle*
//                                                                 |
//                               +-------------+---------+---------+
//                               |             |         |
//                              Car          Bike      Truck

#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

// ---------------- Product interface ----------------
class Vehicle {
public:
    virtual void drive() const = 0;
    virtual int wheels() const = 0;
    virtual string type() const = 0;
    virtual ~Vehicle() = default;
};

// ---------------- Concrete products ----------------
class Car : public Vehicle {
public:
    void drive() const override { cout << "  The car drives smoothly on the road.\n"; }
    int wheels() const override { return 4; }
    string type() const override { return "Car"; }
};

class Bike : public Vehicle {
public:
    void drive() const override { cout << "  The bike zooms through traffic.\n"; }
    int wheels() const override { return 2; }
    string type() const override { return "Bike"; }
};

class Truck : public Vehicle {
public:
    void drive() const override { cout << "  The truck carries heavy cargo slowly.\n"; }
    int wheels() const override { return 6; }
    string type() const override { return "Truck"; }
};

// ---------------- The Factory ----------------
class VehicleFactory {
public:
    // Returns a unique_ptr (single owner). Returns nullptr for an unknown type.
    static unique_ptr<Vehicle> create(const string& requested) {
        if (requested == "car")   return make_unique<Car>();
        if (requested == "bike")  return make_unique<Bike>();
        if (requested == "truck") return make_unique<Truck>();
        return nullptr;
    }
};

int main() {
    cout << "=== Factory pattern demo ===\n";

    vector<string> requests = {"car", "bike", "truck", "plane"};

    for (const string& req : requests) {
        cout << "\nRequesting: " << req << "\n";
        unique_ptr<Vehicle> v = VehicleFactory::create(req);

        if (v) {
            cout << "  Created a " << v->type() << " with " << v->wheels() << " wheels.\n";
            v->drive();
        } else {
            cout << "  Factory error: unknown vehicle type '" << req << "'.\n";
        }
    }

    cout << "\n=== Done ===\n";
    return 0;
}