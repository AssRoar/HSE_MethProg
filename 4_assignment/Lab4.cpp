#include <iostream>
#include <vector>

enum class ScooterState {
    FREE,
    RENTED,
    IN_REPAIR
};

class Scooter {
public:
    ScooterState state;
    int timesRented;
    int timesRepaired;

    Scooter() : state(ScooterState::FREE), timesRented(0), timesRepaired(0) {}

    void rent() {
        state = ScooterState::RENTED;
        timesRented++;
    }

    void returnScooter(bool needsRepair) {
        if (needsRepair) {
            state = ScooterState::IN_REPAIR;
        } else {
            state = ScooterState::FREE;
        }
    }

    void repair() {
        state = ScooterState::FREE;
        timesRepaired++;
    }

    ScooterState getState() const {
        return state;
    }
};

class ScooterPool {
private:
    std::vector<Scooter> scooters;

public:
    ScooterPool(int n) {
        scooters.resize(n);
    }

    Scooter* getScooter() {
        for (auto& scooter : scooters) {
            if (scooter.getState() == ScooterState::FREE) {
                scooter.rent();
                return &scooter;
            }
        }
        return nullptr;
    }

    void returnScooter(Scooter* scooter, bool needsRepair) {
        scooter->returnScooter(needsRepair);
        if (needsRepair) {
            scooter->repair();
        }
    }

    void displayStatistics() {
        int totalRented = 0, totalRepaired = 0;
        for (const auto& scooter : scooters) {
            totalRented += scooter.timesRented;
            totalRepaired += scooter.timesRepaired;
        }
        std::cout << "Total scooters rented: " << totalRented << std::endl;
        std::cout << "Total scooters repaired: " << totalRepaired << std::endl;
    }
};

int main() {
    ScooterPool pool(10); // Pool of 10 scooters

    // Simulate some operations
    Scooter* scooter = pool.getScooter(); // Rent a scooter
    if (scooter != nullptr) {
        pool.returnScooter(scooter, true); // Return and need repair
    }

    scooter = pool.getScooter(); // Rent another scooter
    if (scooter != nullptr) {
        pool.returnScooter(scooter, false); // Return without need for repair
    }

    // Display statistics at the end of the day
    pool.displayStatistics();

    return 0;
}
