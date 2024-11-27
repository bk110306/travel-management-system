
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <memory>
#include <algorithm>

using namespace std;

// Base class for Travel Package
class TravelPackage {
protected:
    string destination;
    int days;
    double cost;

public:
    TravelPackage(const string& dest, int d) : destination(dest), days(d), cost(0) {}

    virtual void calculateCost() = 0;

    virtual void display() const {
        cout << "Destination: " << destination << endl;
        cout << "Duration: " << days << " days" << endl;
        cout << "Total Cost: $" << fixed << setprecision(2) << cost << endl;
    }

    void addFacilityCost(double additionalCost) {
        cost += additionalCost;
    }

    double getCost() const {
        return cost;
    }

    virtual ~TravelPackage() {}
};

// Derived class for Business Class Package
class BusinessClassPackage : public TravelPackage {
public:
    BusinessClassPackage(const string& dest, int d) : TravelPackage(dest, d) {}

    void calculateCost() override {
        cost = days * 500 + 1000; // Business class ticket cost + additional expenses
    }
};

// Derived class for Economy Class Package
class EconomyClassPackage : public TravelPackage {
public:
    EconomyClassPackage(const string& dest, int d) : TravelPackage(dest, d) {}

    void calculateCost() override {
        cost = days * 300 + 500; // Economy class ticket cost + additional expenses
    }
};

// Derived class for Class A Package
class ClassAPackage : public TravelPackage {
public:
    ClassAPackage(const string& dest, int d) : TravelPackage(dest, d) {}

    void calculateCost() override {
        cost = days * 700 + 1500; // Class A ticket cost + additional expenses
    }
};

enum PackageType { SOLO = 2, FAMILY = 1 };

// Traveler class to manage traveler's details
class Traveler {
private:
    string name;
    int age;
    string cnic;

public:
    void inputTravelerDetails() {
        cout << "Enter traveler's name: ";
        getline(cin, name);

        cout << "Enter traveler's age: ";
        cin >> age;

        cin.ignore(); // Ignore newline character
        cout << "Enter traveler's CNIC Number: ";
        getline(cin, cnic);
    }

    void displayTravelerDetails() const {
        cout << "Traveler's Name: " << name << endl;
        cout << "Traveler's Age: " << age << endl;
        cout << "Traveler's CNIC: " << cnic << endl;
    }
};

// InputHandler class to manage input for selecting cities, packages, etc.
class InputHandler {
private:
    vector<string> cities = {"sawat", "kashmir", "naran", "kagan"};

public:
    string selectCity() {
        int selectedCityIndex = -1;

        cout << "Available Cities:" << endl;
        for (size_t i = 0; i < cities.size(); ++i) {
            cout << i + 1 << ". " << cities[i] << endl;
        }

        cout << "Enter the number corresponding to the city: ";
        cin >> selectedCityIndex;

        if (selectedCityIndex < 1 || selectedCityIndex > static_cast<int>(cities.size())) {
            cout << "Invalid city selection!" << endl;
            exit(1);
        }

        // Clear newline character left in the input buffer
        cin.ignore();

        return cities[selectedCityIndex - 1];
    }

    int selectPackageType() {
        int packageType;

        cout << "Select package type:" << endl;
        cout << "1. Family Package (10% discount)" << endl;
        cout << "2. Solo Package (no discount)" << endl;
        cout << "Enter your choice: ";
        cin >> packageType;

        if (packageType != FAMILY && packageType != SOLO) {
            cout << "Invalid package type!" << endl;
            exit(1);
        }

        return packageType;
    }

    int selectPackageDuration() {
        int durationChoice;

        cout << "Select package duration:" << endl;
        cout << "1. 5 days" << endl;
        cout << "2. 10 days" << endl;
        cout << "3. 20 days" << endl;
        cout << "4. 30 days" << endl;

        cout << "Enter your choice: ";
        cin >> durationChoice;

        int days;
        switch (durationChoice) {
            case 1:
                days = 5;
                break;
            case 2:
                days = 10;
                break;
            case 3:
                days = 20;
                break;
            case 4:
                days = 30;
                break;
            default:
                cout << "Invalid choice!" << endl;
                exit(1);
        }

        return days;
    }

    int selectFamilyMembers(int packageType) {
        int familyMembers = 1; // Default to 1 for solo package
        if (packageType == FAMILY) {
            cout << "Enter number of family members: ";
            cin >> familyMembers;
        }
        return familyMembers;
    }

    int selectTicketType(int familyMemberIndex) {
        int ticketType;

        cout << "Select ticket type for family member " << familyMemberIndex + 1 << ":" << endl;
        cout << "1. Business Class (RS 500 per day + RS 1000 fixed)" << endl;
        cout << "2. Economy Class (RS 300 per day + RS 500 fixed)" << endl;
        cout << "3. Class A (RS 700 per day + RS 1500 fixed)" << endl;
        cin >> ticketType;

        if (ticketType < 1 || ticketType > 3) {
            cout << "Invalid ticket type!" << endl;
            exit(1);
        }

        return ticketType;
    }

    vector<string> selectAdditionalFacilities(int days, int familyMembers, double& totalCost) {
        vector<string> facilities;
        int choice;

        do {
            cout << "Additional facilities:" << endl;
            cout << "1. VIP rooms (RS 200)" << endl;
            cout << "2. Regular rooms (RS 100)" << endl;
            cout << "3. Meals (RS 50 per day per person)" << endl;
            cout << "4. Guide (RS 100 per day)" << endl;
            cout << "Enter choice (0 to finish): ";
            cin >> choice;

            switch (choice) {
                case 0:
                    break;
                case 1:
                    facilities.push_back("VIP rooms");
                    totalCost += 200;
                    break;
                case 2:
                    facilities.push_back("Regular rooms");
                    totalCost += 100;
                    break;
                case 3:
                    facilities.push_back("Meals");
                    totalCost += 50 * days * familyMembers;
                    break;
                case 4:
                    facilities.push_back("Guide");
                    totalCost += 100 * days;
                    break;
                default:
                    cout << "Invalid choice!" << endl;
            }
        } while (choice != 0);

        return facilities;
    }
};

int main() {
    Traveler traveler;
    InputHandler inputHandler;

    cout << "Welcome to the Professional Travel Expense Tracker System" << endl;

    traveler.inputTravelerDetails();

    string selectedCity = inputHandler.selectCity();
    int packageType = inputHandler.selectPackageType();
    int days = inputHandler.selectPackageDuration();
    int familyMembers = inputHandler.selectFamilyMembers(packageType);

    double totalCost = 0;
    vector<unique_ptr<TravelPackage>> packages;

    for (int i = 0; i < familyMembers; ++i) {
        int ticketType = inputHandler.selectTicketType(i);

        unique_ptr<TravelPackage> package;
        switch (ticketType) {
            case 1:
                package = make_unique<BusinessClassPackage>(selectedCity, days);
                break;
            case 2:
                package = make_unique<EconomyClassPackage>(selectedCity, days);
                break;
            case 3:
                package = make_unique<ClassAPackage>(selectedCity, days);
                break;
        }

        package->calculateCost();
        packages.push_back(move(package));
    }

    vector<string> facilities = inputHandler.selectAdditionalFacilities(days, familyMembers, totalCost);

    cout << "\nDetailed Breakdown:" << endl;
    double packageTotal = 0;
    for (const auto& package : packages) {
        package->display();
        packageTotal += package->getCost();
    }

    cout << "\nAdditional Facilities:" << endl;
    for (const auto& facility : facilities) {
        cout << "- " << facility << endl;
    }

    totalCost += packageTotal;

    if (packageType == FAMILY) {
        double discountedAmount = packageTotal * 0.10;
        double totalBillAfterDiscount = totalCost - discountedAmount;

        cout << "\nTotal Amount before Discount: RS" << fixed << setprecision(2) << totalCost << endl;
        cout << "Discounted Amount: RS" << fixed << setprecision(2) << discountedAmount << endl;
        cout << "Total Bill after Discount: RS" << fixed << setprecision(2) << totalBillAfterDiscount << endl;
    } else {
        cout << "\nTotal Cost: RS" << fixed << setprecision(2) << totalCost << endl;
    }

    return 0;
}
