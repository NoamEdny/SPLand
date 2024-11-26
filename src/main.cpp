//#include "Simulation.h"

#include "Facility.h"
#include "Settlement.h"
#include <iostream>
#include "SelectionPolicy.h"
using std::string;
using std::vector;
using namespace std;

//Simulation* backup = nullptr;

 /*int main(int argc, char** argv){
 
   if(argc!=2){
        cout << "usage: simulation <config_path>" << endl;
        return 0;
    }
    string configurationFile = argv[1];
    Simulation simulation(configurationFile);
    simulation.start();
    if(backup!=nullptr){
    	delete backup;
    	backup = nullptr;
  */ 


int main() {
   // Create a settlement
    Settlement village("KfarSP", SettlementType::VILLAGE);
    cout << "hiiii" << endl;
    // Create facilities and add them to a vector

    vector<FacilityType> facilities;
facilities.push_back(FacilityType("school", FacilityCategory::LIFE_QUALITY, 5, 3, 1, 2));
facilities.push_back(FacilityType("hospital", FacilityCategory::ECONOMY, 7, 2, 5, 1));
facilities.push_back(FacilityType("park", FacilityCategory::LIFE_QUALITY, 3, 4, 1, 3));


    // Print settlement details
    cout << "Settlement Details:" << endl;
    cout << "Name: " << village.getName()
         << ", Type: " << (village.getType() == SettlementType::VILLAGE ? "Village" : "Unknown")
         << endl;

    // Print facility details
    cout << "Facility Details:" << endl;
    for (const auto& facility : facilities) {
        cout << "Facility: " << facility.getName() << ", Category: " 
             << (facility.getCategory() == FacilityCategory::LIFE_QUALITY ? "Life Quality" : "Economy")
             << ", Cost: " << facility.getCost() << endl;
    }

    // SelectionPolicy Tests
    cout << "\nTesting Selection Policies:" << endl;

    // Naive Selection Policy
    NaiveSelection naivePolicy;
    const FacilityType& selectedFacilityNaive = naivePolicy.selectFacility(facilities);
    cout << "Naive Policy selected: " << selectedFacilityNaive.getName() << endl;

    // Balanced Selection Policy
    BalancedSelection balancedPolicy(10, 5, 8); // Initial scores for Life Quality, Economy, Environment
    const FacilityType& selectedFacilityBalanced = balancedPolicy.selectFacility(facilities);
    cout << "Balanced Policy selected: " << selectedFacilityBalanced.getName() << endl;

    // Economy Selection Policy
    EconomySelection economyPolicy;
    const FacilityType& selectedFacilityEconomy = economyPolicy.selectFacility(facilities);
    cout << "Economy Policy selected: " << selectedFacilityEconomy.getName() << endl;

    return 0;
}
