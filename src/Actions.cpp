#include "Action.h"
#include <iostream>
using namespace std;
using std::string;

//***********************************************************************************************************

//************************************************  SimulateStep ************************************************

//Constractor
SimulateStep::SimulateStep(const int numOfSteps) : numOfSteps(numOfSteps) {}

SimulateStep::SimulateStep() : numOfSteps(1) {}

void SimulateStep::act(Simulation &simulation) {
    //Iterete thro all curent plans
    for (int id =0; id < simulation.getPlanCounter(); id++){
        Plan &plan = simulation.getPlan(id); //using & because we want to change the plan in the simulation
        //Step each plan numOfSteps:
        for(int i = 0; i < numOfSteps; i++){
            plan.step();
        }
    }
    complete();
 }

 const string SimulateStep::toString() const{
    return "Step: " + std::to_string(numOfSteps);
 }

 SimulateStep *SimulateStep::clone() const{
    return new SimulateStep(*this);
 }

//***********************************************************************************************************

//************************************************  AddPlan ************************************************

//Constractor:
AddPlan::AddPlan(const string &settlementName, const string &selectionPolicy):
 settlementName(settlementName), selectionPolicy(selectionPolicy){}

//Methods:
void AddPlan::act(Simulation &simulation){
    SelectionPolicy *newPolicy;
    if(!(selectionPolicy == "nve" ||  selectionPolicy == "bal" || selectionPolicy == "eco" || selectionPolicy == "env") // selectionPolicy is legal
     || !simulation.isSettlementExists(settlementName)) //settlementName is not in the settlements in the Simulation
     {
        error("Can't create this plan :(");
     }
    else if (selectionPolicy == "nve"){
        newPolicy = new NaiveSelection();
    }
    else if(selectionPolicy == "bal"){
        newPolicy = new BalancedSelection();
    }
    else if (selectionPolicy == "eco"){
        newPolicy = new EconomySelection();
    }
    else if(selectionPolicy == "env"){
        newPolicy = new SustainabilitySelection();
    }
    simulation.addPlan(simulation.getSettlement(settlementName), newPolicy);
    complete();
}

const string AddPlan::toString() const{
    return "Plan: " + settlementName + selectionPolicy;
}

AddPlan *AddPlan::clone() const{
    return new AddPlan(*this);
}

//***********************************************************************************************************

//************************************************ AddSettlement ************************************************

//Constractor:
AddSettlement::AddSettlement(const string &settlementName,SettlementType settlementType):
settlementName(settlementName), settlementType(settlementType){}

//Methods:
void AddSettlement::act(Simulation &simulation){
    if(simulation.isSettlementExists(settlementName)){
        error("Settelment alredy exists");
    }
    else{
        Settlement *newSettlment = new Settlement(settlementName,settlementType);
        simulation.addSettlement(newSettlment);
    }
}

const string AddSettlement::toString() const{
    return "Settlement: " + settlementName + " " + std::to_string(static_cast<int>(settlementType));
}

AddSettlement *AddSettlement::clone() const{
    return new AddSettlement(*this);
}


