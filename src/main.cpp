<<<<<<< HEAD
//#include "Simulation.h"
#include "Settlement.h"
=======
/*#include "Simulation.h"
>>>>>>> 330a2be6bab3daffe255d15b35f3debc1dca77ef
#include <iostream>
#include "Settlement.h"

using namespace std;

<<<<<<< HEAD
//Simulation* backup = nullptr;
=======
// Simulation* backup = nullptr;
>>>>>>> 330a2be6bab3daffe255d15b35f3debc1dca77ef

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

<<<<<<< HEAD
cout << "hiii" << endl;
=======
>>>>>>> 330a2be6bab3daffe255d15b35f3debc1dca77ef
    return 0;
}
