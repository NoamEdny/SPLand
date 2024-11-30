#include "Simulation.h"
#include "Auxiliary.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

Simulation::Simulation(const string &configFilePath)
    : isRunning(false), planCounter(0) // Default initialization
{
    ifstream configFile(configFilePath);
    string line;
    while (getline(configFile, line)) {
        // Skip empty lines or comments
        if (line.empty() || line[0] == '#') {
            continue;
        }
        // Parse the line
        vector<string> tokens = Auxiliary::parseArguments(line);

        // Process based on the type of the line
        if (tokens[0] == "settlement") {
            addSettlement(new Settlement(tokens[1], static_cast<SettlementType>(stoi(tokens[2]))));
        } else if (tokens[0] == "facility") {
            addFacility(FacilityType(tokens[1], static_cast<FacilityCategory>(stoi(tokens[2])),
                stoi(tokens[3]), stoi(tokens[4]), stoi(tokens[5]), stoi(tokens[6])));
        } else if (tokens[0] == "plan") {
            addPlan(getSettlement(tokens[1]), getSelectionPolicy(tokens[2])); //"getSelectionPolicy" cerate a new SelectionPolic - it's going to be deletad by the destrector of the plan
        }
    }
    configFile.close();
}

void Simulation::start(){
    isRunning = true; // Indicates that the simulation is running
    cout << "Simulation started!" << endl;

    while (isRunning) {
        string line;
        cin >> line;
        vector<string> tokens = Auxiliary::parseArguments(line);
        if (tokens[0] == "settlement") {
            BaseAction *newSettlement = new AddSettlement(tokens[1], static_cast<SettlementType>(stoi(tokens[2])));
            newSettlement->act(*this);
            addAction(newSettlement);
        } 
        else if (tokens[0] == "facility") {
            BaseAction *newFacility = new AddFacility(tokens[1], static_cast<FacilityCategory>(stoi(tokens[2])), stoi(tokens[3]),
            stoi(tokens[3]),stoi(tokens[4]),stoi(tokens[5]));
            newFacility->act(*this);
            addAction(newFacility);
        } 
        else if (tokens[0] == "plan") {
            BaseAction *newPlan = new AddPlan(tokens[1], tokens[2]);
            newPlan ->act(*this);
            addAction(newPlan);
        } 
        else if (tokens[0] == "step") {
        // Placeholder for additional conditions
            BaseAction *newStep = new SimulateStep(stoi(tokens[1]));
            newStep ->act(*this);
            addAction(newStep);
        }
        else if (tokens[0] == "planStatus") {
            BaseAction *planStatus = new PrintPlanStatus(stoi(tokens[1]));
            planStatus ->act(*this);
            addAction(planStatus);
        } 
        else if (tokens[0] == "changePolicy") {
            BaseAction *changePolicy = new ChangePlanPolicy(stoi(tokens[1]), tokens[2]);
            changePolicy ->act(*this);
            addAction(changePolicy);
        } 
        else if (tokens[0] == "log") {
            BaseAction *printActionsLog = new PrintActionsLog();
            printActionsLog ->act(*this);
            addAction(printActionsLog);
        }
        else if (tokens[0] == "close") {
            BaseAction *close = new Close();
            close ->act(*this);
            addAction(close);
        }  
        else if (tokens[0] == "backup") {
            BaseAction *backupSimulation = new BackupSimulation();
            backupSimulation ->act(*this);
            addAction(backupSimulation);
        }  
        else if (tokens[0] == "restore") {
            BaseAction *restoreSimulation = new RestoreSimulation();
            restoreSimulation ->act(*this);
            addAction(restoreSimulation);
        }  
    }
}
