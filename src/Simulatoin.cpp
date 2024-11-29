#include "Simulation.h"
#include "Auxiliary.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

Simulation::Simulation(const string &configFilePath)
    : isRunning(false), planCounter(0) // אתחול ברירת מחדל
{
    ifstream configFile(configFilePath);

    string line;
    while (getline(configFile, line)) {
        // דלג על שורות ריקות או הערות
        if (line.empty() || line[0] == '#') {
            continue;
        }
        // נתח את השורה
        vector<string> tokens = Auxiliary::parseArguments(line);

        // עיבוד לפי סוג השורה
        if (tokens[0] == "settlement") {
            addSettlement(new Settlement(tokens[1], static_cast<SettlementType>(stoi(tokens[2]))));
        } else if (tokens[0] == "facility") {
            addFacility(FacilityType(tokens[1], static_cast<FacilityCategory>(stoi(tokens[2])),
                stoi(tokens[3]), stoi(tokens[4]), stoi(tokens[5]), stoi(tokens[6])));
        } else if (tokens[0] == "plan") {
            addPlan(getSettlement(tokens[1]), getSelectionPolicy(tokens[2]));
        }
    }
    configFile.close();
}
void Simulation::start(){
     isRunning = true; // מסמן שהסימולציה פועלת
    cout << "Simulation started!" << endl;

     while (isRunning) {
        string line;
        cin >> line;

        vector<string> tokens = Auxiliary::parseArguments(line);
         if (tokens[0] == "settlement") {
            BaseAction *newSettelment = new AddSettlement(tokens[1], static_cast<SettlementType>(stoi(tokens[2])));
            
        } else if (tokens[0] == "facility") {
            addFacility(FacilityType(tokens[1], static_cast<FacilityCategory>(stoi(tokens[2])),
                stoi(tokens[3]), stoi(tokens[4]), stoi(tokens[5]), stoi(tokens[6])));
        } else if (tokens[0] == "plan") {
            addPlan(getSettlement(tokens[1]), getSelectionPolicy(tokens[2]));
        }
        else if ()
     }
}