//#include "Simulation.h"

#include "Facility.h"
#include "Settlement.h"
#include <iostream>
#include "SelectionPolicy.h"
#include "Plan.h"
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
 try {
        // יצירת ישוב
        Settlement city("TestCity", SettlementType::CITY);
        cout << "Settlement created: " << city.toString() << endl;

        // יצירת מתקנים
        FacilityType school("School", FacilityCategory::LIFE_QUALITY, 3, 2, 1, 0);
        FacilityType factory("Factory", FacilityCategory::ECONOMY, 5, 0, 3, 1);
        FacilityType park("Park", FacilityCategory::ENVIRONMENT, 4, 1, 0, 3);

        vector<FacilityType> facilities = {school, factory, park};

        // יצירת מדיניות בחירה נאיבית
        NaiveSelection naivePolicy;
        // יצירת תוכנית עם הישוב והמדיניות
        Plan plan(1, city, &naivePolicy, facilities);
        cout << "\nPlan created:\n" << plan.toString() << endl;

        // ביצוע שלב ראשון
        cout << "\nExecuting first step...\n";
        plan.step();
        cout << "Plan after first step:\n" << plan.toString() << endl;

        // מעבר למדיניות בחירה מאוזנת
        BalancedSelection balancedPolicy;
        cout << "\nChanging selection policy to Balanced...\n";
        plan.setSelectionPolicy(&balancedPolicy);

        // ביצוע שלב נוסף
        cout << "\nExecuting second step...\n";
        plan.step();
        cout << "Plan after second step:\n" << plan.toString() << endl;
    } catch (const exception &e) {
        cerr << "An error occurred: " << e.what() << endl;
    }

    return 0;
}