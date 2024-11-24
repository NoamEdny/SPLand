//#include "Simulation.h"

#include "Facility.h"
#include "Settlement.h"
#include <iostream>

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
    // difind
    Settlement village("KfarSP", SettlementType::VILLAGE);
    Facility school("school", "KfarSP", FacilityCategory::LIFE_QUALITY, 5, 0, 0, 0);


    // print
    cout << "Settlement Details:" << endl;

    cout << "Name: " << village.getName() 
         << ", Type: " << (village.getType() == SettlementType::VILLAGE ? "Village" : "Unknown") 
         << endl;
    
    cout << "Facility Details:" << endl;
    cout << school.toString();


cout << "hiii" << endl;
    return 0;
}
