#include <iostream>
#include <string>
#include <vector>
#include <memory>

// this class handles trip info
class TravelPlan {
protected:
    int tID;
    std::string origin;
    std::string destination;
    double miles;
    double cost;

public:
    TravelPlan(int id, std::string o, std::string d, double m)
        : tID(id), origin(o), destination(d), miles(m), cost(0.0) {}

    virtual double computeCost() = 0;   // cost calculation
    virtual void showPlan() {
        std::cout << "Trip " << tID
                  << "  From: " << origin
                  << "  To: " << destination
                  << "  Miles: " << miles
                  << "  Cost: $" << cost << std::endl;
    }

    virtual ~TravelPlan() {}
};

// this class handles basic trips
class BasicTrip : public TravelPlan {
public:
    BasicTrip(int id, std::string o, std::string d, double m)
        : TravelPlan(id, o, d, m) {}

    double computeCost() override {
        cost = miles * 1.40 + 2.0;
        return cost;
    }

    void showPlan() override {
        std::cout << "[Basic] ";
        TravelPlan::showPlan();
    }
};

// this class handles premium trips
class PremiumTrip : public TravelPlan {
public:
    PremiumTrip(int id, std::string o, std::string d, double m)
        : TravelPlan(id, o, d, m) {}

    double computeCost() override {
        cost = miles * 2.20 + 5.0;
        return cost;
    }

    void showPlan() override {
        std::cout << "[Premium] ";
        TravelPlan::showPlan();
    }
};

// this class handles drivers
class Captain {
private:
    int capID;
    std::string capName;
    double rating;
    std::vector<TravelPlan*> trips;  // private data

public:
    Captain(int id, std::string n, double r)
        : capID(id), capName(n), rating(r) {}

    void addTrip(TravelPlan* t) {
        trips.push_back(t);
    }

    void showCaptain() {
        std::cout << "\nCaptain: " << capName
                  << " | Rating: " << rating << std::endl;
        for (auto t : trips)
            t->showPlan();
    }
};

// this class handles riders
class Commuter {
private:
    int userID;
    std::string userName;
    std::vector<TravelPlan*> history;  // private data

public:
    Commuter(int id, std::string n)
        : userID(id), userName(n) {}

    void request(TravelPlan* t) {
        history.push_back(t);
    }

    void showHistory() {
        std::cout << "\nCommuter: " << userName << std::endl;
        for (auto h : history)
            h->showPlan();
    }
};

// this function runs the system
int main() {

    std::vector<std::unique_ptr<TravelPlan>> rideList;

    rideList.push_back(std::make_unique<BasicTrip>(10, "West Gate", "Lake Park", 6.5));
    rideList.push_back(std::make_unique<PremiumTrip>(11, "Central Hub", "North Square", 14.0));

    std::cout << "=== Trip Summary ===" << std::endl;
    for (auto& r : rideList) {
        r->computeCost();
        r->showPlan();     // polymorphism used here
    }

    Captain d1(101, "Marcus Lee", 4.7);
    Commuter r1(201, "Sara Lin");

    d1.addTrip(rideList[0].get());
    d1.addTrip(rideList[1].get());

    r1.request(rideList[0].get());
    r1.request(rideList[1].get());

    d1.showCaptain();
    r1.showHistory();

    return 0;
}
