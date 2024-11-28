#include "Action.h"


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
    return "SimulateStep: " + std::to_string(numOfSteps);
 }

 SimulateStep *SimulateStep::clone() const{
    return new SimulateStep(*this);
 }

//***********************************************************************************************************

//************************************************  AddPlan ************************************************

//Constractor:
AddPlan::AddPlan(const string &settlementName, const string &selectionPolicy):
 settlementName(settlementName), selectionPolicy(selectionPolicy){}

void AddPlan::act(Simulation &simulation){
    SelectionPolicy *newPolicy;
    if (selectionPolicy == "nve"){
        newPolicy = new NaiveSelection();
        simulation.addPlan(simulation.getSettlement(settlementName), newPolicy);
    }
    else if(selectionPolicy == "bal"){
        newPolicy = new BalancedSelection();
        simulation.addPlan(simulation.getSettlement(settlementName), newPolicy);
    }
    else if (selectionPolicy == "eco"){
        newPolicy = new EconomySelection();
        simulation.addPlan(simulation.getSettlement(settlementName), newPolicy);
    }
    else if(selectionPolicy == "env"){
        newPolicy = new SustainabilitySelection();
        simulation.addPlan(simulation.getSettlement(settlementName), newPolicy);
    }
    else{
        error("no legal selection policy string :(");
    }
}