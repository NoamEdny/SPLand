#pragma once
#include <string>
#include <vector>
#include "Facility.h"
#include "Plan.h"
#include "Settlement.h"
#include "Action.h"
using std::string;
using std::vector;

class BaseAction;
class SelectionPolicy;

class Simulation {
    public:
        //Consractor:
        Simulation(const string &configFilePath);
        Simulation(); //TOdO
    //Rule Of 3:
        // Copy-Constructor:
        Simulation(const Simulation &other);
        void start();  
        void addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy);
        void addAction(BaseAction *action); //TO DO
        bool addSettlement(Settlement *settlement);
        bool addFacility(FacilityType facility);
        bool isSettlementExists(const string &settlementName);
        Settlement &getSettlement(const string &settlementName);
        SelectionPolicy *getSelectionPolicy (const string &selectionPolicy);
        SelectionPolicy *getSelectionPolicy (const string &selectionPolicy, int LifeQualityScore, int EconomyScore, int EnvironmentScore);
        void setSelectionPolicy  (const string &selectionPolicy, int planID);
        int getPlanCounter() const;
        Plan &getPlan(const int planID);
        vector<BaseAction*> getActionsLog();
        void step();
        void close();
        void open();

    private:
        bool isRunning;
        int planCounter; //For assigning unique plan IDs
        vector<BaseAction*> actionsLog;
        vector<Plan> plans;
        vector<Settlement*> settlements;
        vector<FacilityType> facilitiesOptions;
//where we are pushing the actions in to log
};