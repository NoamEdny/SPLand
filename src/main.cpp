#include "Simulation.h"
#include <iostream>

using namespace std;

 Simulation* backup = nullptr;

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

if (argc > 1) {
    std::cout << "First argument" << argv[1] << std::endl;
}
else {
    std::cout << "No argument provided" << std::endl;
}
    return 0;
}