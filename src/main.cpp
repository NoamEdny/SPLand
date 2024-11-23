/*#include "Simulation.h"
#include <iostream>
#include "Settlement.h"

using namespace std;

// Simulation* backup = nullptr;

int main(int argc, char** argv){
  /*
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
#include <iostream>
#include "Settlement.h"

using namespace std;

int main() {
    // יצירת אובייקטים מסוג Settlement
    Settlement village("KfarSP", SettlementType::VILLAGE);
    Settlement city("TelSP", SettlementType::CITY);
    Settlement metropolis("SPopolis", SettlementType::METROPOLIS);

    // הדפסת פרטי היישובים
    cout << "Settlement Details:" << endl;

    cout << "Name: " << village.getName() 
         << ", Type: " << (village.getType() == SettlementType::VILLAGE ? "Village" : "Unknown") 
         << endl;

    cout << "Name: " << city.getName() 
         << ", Type: " << (city.getType() == SettlementType::CITY ? "City" : "Unknown") 
         << endl;

    cout << "Name: " << metropolis.getName() 
         << ", Type: " << (metropolis.getType() == SettlementType::METROPOLIS ? "Metropolis" : "Unknown") 
         << endl;

    return 0;
}
