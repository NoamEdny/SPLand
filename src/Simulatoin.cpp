#include "Simulation.h"
#include "Auxiliary.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

//Consractor
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

//Rule Of 3:
// Copy-Constructor:
Simulation::Simulation(const Simulation &other){
    //actionsLog:
    for(BaseAction *action : other.actionsLog){
        actionsLog.push_back(action->clone());
    }
    //Plan (it's may seems like we don't need deep copy, but Plan has a pointer field)
    for(Plan plan : other.plans){
        plans.push_back(Plan(plan));
    }

    //settlements:
    for(Settlement *settlement : other.settlements){
        settlements.push_back(new Settlement(*settlement));
    }

    facilitiesOptions = other.facilitiesOptions; //we dont need to do deep copy
    
    isRunning = other.isRunning;
    planCounter = other.planCounter;
}




void Simulation::start(){
    open(); // Indicates that the simulation is running

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

void Simulation::step(){
    for(Plan planStep : plans){
        planStep.step();
    }
}

void Simulation::addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy){
    Plan newPlan = Plan(planCounter,settlement,selectionPolicy, this->facilitiesOptions);
    plans.push_back(newPlan);
    planCounter += 1;
}

bool Simulation::addSettlement(Settlement *settlement){
        settlements.push_back(settlement);
        return true;
}

bool Simulation::addFacility(FacilityType facility){
    bool isFacilityExist = false;
    for (FacilityType facilityOption : facilitiesOptions){
        isFacilityExist = facilityOption == facility;
    }
    if (!isFacilityExist){
        facilitiesOptions.push_back(facility);
        return true;
    }
    else{
        return false;
    }    
}

bool Simulation::isSettlementExists(const string &settlementName){
    for(Settlement *settlement : settlements){
        if (settlement->getName() == settlementName){
            return true;
        }
    }
    return false;
}

Settlement &Simulation::getSettlement(const string &settlementName){
    for(Settlement *settlement : settlements){
        if (settlement->getName() == settlementName){
            return *settlement;
        }
    }
    Settlement defaultSettlement = Settlement();
    return defaultSettlement;
}

SelectionPolicy *Simulation::getSelectionPolicy (const string &selectionPolicy, int LifeQualityScore, int EconomyScore, int EnvironmentScore){
    if(selectionPolicy == "nev"){
        return new NaiveSelection();
    }
    else if(selectionPolicy == "eco"){
        return new EconomySelection();
    }
    else if(selectionPolicy == "env"){
        return new SustainabilitySelection();
    }
    else if(selectionPolicy == "bal"){
        return new BalancedSelection(LifeQualityScore,EconomyScore,EnvironmentScore);
    }
}

SelectionPolicy *Simulation::getSelectionPolicy (const string &selectionPolicy){
    return getSelectionPolicy(selectionPolicy,0,0,0);
}

int Simulation::getPlanCounter() const{
    return planCounter;
}

Plan &Simulation::getPlan(const int planID){
    return plans[planID];
}

void Simulation::close(){
    for(Plan plan : plans){
        cout << plan.toString()  +"\n"<< endl;
    }
    isRunning = false;
}

void Simulation::open(){
    isRunning - true;
    cout << "Simulation started!" << endl;
}

void Simulation::setSelectionPolicy(const string &selectionPolicy, int planID) {
    Plan &plan = getPlan(planID); // שימוש בהפניה כדי לעדכן ישירות את התוכנית
    SelectionPolicy *policy = nullptr;

    if (selectionPolicy == "Naive") {
        policy = new NaiveSelection();
    } else if (selectionPolicy == "Balanced") {
        policy = new BalancedSelection(plan.getlifeQualityScore(), plan.getEconomyScore(), plan.getEnvironmentScore());
    } else if (selectionPolicy == "Economy") {
        policy = new EconomySelection();
    } else if (selectionPolicy == "Sustainability") {
        policy = new SustainabilitySelection();
    }

    if (policy) {
        plan.setSelectionPolicy(policy); 
    } else {
        throw runtime_error("Invalid selection policy");
    }
}

vector<BaseAction*> Simulation::getActionsLog(){
    return actionsLog;
}
