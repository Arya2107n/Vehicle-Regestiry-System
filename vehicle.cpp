#include <iostream>
#include <string>
using namespace std;

class Vehicle {
protected:
    int vehicleID;
    string manufacturer;
    string model;
    int year;

    static int totalVehicles;

public:
    Vehicle() : vehicleID(0), manufacturer(""), model(""), year(0) {
        totalVehicles++;
    }

    Vehicle(int id, const string& manu, const string& mod, int yr)
        : vehicleID(id), manufacturer(manu), model(mod), year(yr) {
        totalVehicles++;
    }

    virtual ~Vehicle() {
        totalVehicles--;
    }

    int getVehicleID() const { return vehicleID; }
    static int getTotalVehicles() { return totalVehicles; }

    virtual void display() const {
        cout << "ID: " << vehicleID
             << ", Manufacturer: " << manufacturer
             << ", Model: " << model
             << ", Year: " << year;
    }
};

int Vehicle::totalVehicles = 0;

class Car : public Vehicle {
protected:
    string fuelType;

public:
    Car() : Vehicle(), fuelType("") {}

    Car(int id, const string& manu, const string& mod, int yr, const string& fuel)
        : Vehicle(id, manu, mod, yr), fuelType(fuel) {}

    void display() const override {
        Vehicle::display();
        cout << ", Fuel Type: " << fuelType;
    }
};

class ElectricCar : public Car {
protected:
    int batteryCapacity;

public:
    ElectricCar() : Car(), batteryCapacity(0) {}

    ElectricCar(int id, const string& manu, const string& mod,
                int yr, const string& fuel, int cap)
        : Car(id, manu, mod, yr, fuel), batteryCapacity(cap) {}

    void display() const override {
        Car::display();
        cout << ", Battery Capacity: " << batteryCapacity << " kWh";
    }
};

class Aircraft {
protected:
    int flightRange;

public:
    Aircraft() : flightRange(0) {}
    Aircraft(int fr) : flightRange(fr) {}
    virtual ~Aircraft() {}

    void displayAircraft() const {
        cout << ", Flight Range: " << flightRange << " km";
    }
};

class FlyingCar : public Car, public Aircraft {
public:
    FlyingCar() : Car(), Aircraft() {}

    FlyingCar(int id, const string& manu, const string& mod,
              int yr, const string& fuel, int fr)
        : Car(id, manu, mod, yr, fuel), Aircraft(fr) {}

    void display() const override {
        Car::display();
        displayAircraft();
    }
};

class SportsCar : public ElectricCar {
    int topSpeed;

public:
    SportsCar() : ElectricCar(), topSpeed(0) {}

    SportsCar(int id, const string& manu, const string& mod,
              int yr, const string& fuel, int cap, int ts)
        : ElectricCar(id, manu, mod, yr, fuel, cap), topSpeed(ts) {}

    void display() const override {
        ElectricCar::display();
        cout << ", Top Speed: " << topSpeed << " km/h";
    }
};

class Sedan : public Car {
public:
    Sedan() : Car() {}

    Sedan(int id, const string& manu, const string& mod,
          int yr, const string& fuel)
        : Car(id, manu, mod, yr, fuel) {}

    void display() const override {
        Car::display();
        cout << " (Sedan)";
    }
};

class SUV : public Car {
public:
    SUV() : Car() {}

    SUV(int id, const string& manu, const string& mod,
        int yr, const string& fuel)
        : Car(id, manu, mod, yr, fuel) {}

    void display() const override {
        Car::display();
        cout << " (SUV)";
    }
};

class VehicleRegistry {
    Vehicle* vehicles[100];
    int count;

public:
    VehicleRegistry() : count(0) {}

    ~VehicleRegistry() {
        for (int i = 0; i < count; i++) {
            delete vehicles[i];
        }
    }

    void addVehicle(Vehicle* v) {
        if (count < 100) {
            vehicles[count++] = v;
        } else {
            cout << "Registry Full!\n";
        }
    }

    void displayAll() const {
        if (count == 0) {
            cout << "No vehicles available.\n";
            return;
        }

        for (int i = 0; i < count; i++) {
            vehicles[i]->display();
            cout << endl;
        }
    }

    Vehicle* searchById(int id) const {
        for (int i = 0; i < count; i++) {
            if (vehicles[i]->getVehicleID() == id)
                return vehicles[i];
        }
        return nullptr;
    }
};

void menu() {
    cout << "\n--- Vehicle Registry System ---\n";
    cout << "1. Add Vehicle\n";
    cout << "2. View All Vehicles\n";
    cout << "3. Search by ID\n";
    cout << "4. Exit\n";
    cout << "Enter choice: ";
}

int main() {
    VehicleRegistry registry;
    int choice;

    do {
        menu();
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "\nVehicle Types:\n";
            cout << "1. Car\n2. ElectricCar\n3. FlyingCar\n4. SportsCar\n5. Sedan\n6. SUV\n";

            int vtype;
            cout << "Select type (1-6): ";
            cin >> vtype;

            int id, yr, cap, fr, ts;
            string manu, mod, fuel;
            Vehicle* v = nullptr;

            cout << "Enter ID, Manufacturer, Model, Year: ";
            cin >> id >> manu >> mod >> yr;

            switch (vtype) {
            case 1:
                cout << "Enter Fuel Type: ";
                cin >> fuel;
                v = new Car(id, manu, mod, yr, fuel);
                break;

            case 2:
                cout << "Enter Fuel Type and Battery Capacity: ";
                cin >> fuel >> cap;
                v = new ElectricCar(id, manu, mod, yr, fuel, cap);
                break;

            case 3:
                cout << "Enter Fuel Type and Flight Range: ";
                cin >> fuel >> fr;
                v = new FlyingCar(id, manu, mod, yr, fuel, fr);
                break;

            case 4:
                cout << "Enter Fuel Type, Battery Capacity and Top Speed: ";
                cin >> fuel >> cap >> ts;
                v = new SportsCar(id, manu, mod, yr, fuel, cap, ts);
                break;

            case 5:
                cout << "Enter Fuel Type: ";
                cin >> fuel;
                v = new Sedan(id, manu, mod, yr, fuel);
                break;

            case 6:
                cout << "Enter Fuel Type: ";
                cin >> fuel;
                v = new SUV(id, manu, mod, yr, fuel);
                break;

            default:
                cout << "Invalid type!\n";
            }

            if (v) registry.addVehicle(v);
            break;
        }

        case 2:
            registry.displayAll();
            break;

        case 3: {
            int id;
            cout << "Enter Vehicle ID to search: ";
            cin >> id;

            Vehicle* v = registry.searchById(id);
            if (v)
                v->display();
            else
                cout << "Not found!";
            cout << endl;
            break;
        }

        case 4:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice!";
        }

    } while (choice != 4);

    return 0;
}

