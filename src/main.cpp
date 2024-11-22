#include "Simulation.h"
#include <iostream>

using namespace std;

Simulation* backup = nullptr;

int main(int argc, char** argv){
    /*if(argc!=2){
        cout << "usage: simulation <config_path>" << endl;
        return 0;
    }
    string configurationFile = argv[1];
    Simulation simulation(configurationFile);
    simulation.start();
    if(backup!=nullptr){
    	delete backup;
    	backup = nullptr;
    }
    */
    Settlement village("GreenVillage", SettlementType::VILLAGE);
    Settlement city("BigCity", SettlementType::CITY);
    Settlement metropolis("MegaMetro", SettlementType::METROPOLIS);
std::cout << village.toString() << std::endl;
    std::cout << city.toString() << std::endl;
    std::cout << metropolis.toString() << std::endl;
    std::cout << copiedCity.toString() << std::endl;

    return 0;
}