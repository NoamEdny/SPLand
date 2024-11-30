#include "Action.h"
#include <iostream>
using namespace std;
using std::string;

ActionStatus BaseAction::getStatus() const {
    return status;
}

void BaseAction::complete() {
    status = ActionStatus::COMPLETED;
}

void BaseAction::error(string errorMsg){
    status = ActionStatus::ERROR;
    cout << errorMsg << endl;
}

string BaseAction::statusToString(ActionStatus status) const{
    string result;
    switch (status) {
        case ActionStatus::COMPLETED:
            result = "COMPLETED";
            break;
        case ActionStatus::ERROR:
            result = "ERROR";
            break;
    }
    return result;
}

//***********************************************************************************************************

//************************************************  SimulateStep ************************************************

//Constractor
SimulateStep::SimulateStep(const int numOfSteps) : numOfSteps(numOfSteps) {}

SimulateStep::SimulateStep() : numOfSteps(1) {}

void SimulateStep::act(Simulation &simulation) {
    //Iterete thro all curent plans
    for (int i =0; i < numOfSteps; i++){
        simulation.step();
        }
    complete();
 }

 const string SimulateStep::toString() const{
    return "Step: " + std::to_string(numOfSteps) + statusToString(getStatus());
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
    if (!simulation.isSettlementExists(settlementName)){
        error("Cannot creat this plan");
    }
    else {
        simulation.addPlan(simulation.getSettlement(settlementName), simulation.getSelectionPolicy(selectionPolicy));
         complete();
    }
}

const string AddPlan::toString() const{
    return "Plan: " + settlementName + selectionPolicy + statusToString(getStatus());
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
       simulation.addSettlement(new Settlement(settlementName, settlementType));
        complete();
    }
}

const string AddSettlement::toString() const{
    return "Settlement: " + settlementName + " " + std::to_string(static_cast<int>(settlementType)) + statusToString(getStatus());
}

AddSettlement *AddSettlement::clone() const{
    return new AddSettlement(*this);
}


//***********************************************************************************************************

//************************************************ AddFacility ************************************************

//Constractor:
AddFacility::AddFacility(const string &facilityName, const FacilityCategory facilityCategory, 
const int price, const int lifeQualityScore, const int economyScore, const int environmentScore) : 
facilityName(facilityName), facilityCategory(facilityCategory), price(price), lifeQualityScore(lifeQualityScore), 
economyScore(economyScore), environmentScore(environmentScore) {}

//Methods:
void AddFacility::act(Simulation &simulation){
    if (simulation.addFacility(FacilityType(facilityName, facilityCategory, price, lifeQualityScore, economyScore, environmentScore))){
            complete();
    }
    else {
        error ("Facility already exist");
    }
}
const string AddFacility::toString() const{
        return "facility " + facilityName + " " + std::to_string(static_cast<int>(facilityCategory)) 
        +"price"+ std::to_string(price) +" " + std::to_string(lifeQualityScore) +" " + std::to_string(economyScore) +
         " " + std::to_string(environmentScore) + statusToString(getStatus());
}
AddFacility *AddFacility::clone() const{
    return new AddFacility(*this);
}

//***********************************************************************************************************

//************************************************ PrintPlanStatus ************************************************

//Constractor
PrintPlanStatus::PrintPlanStatus(int planId) : planId(planId) {}

//Methods:
void PrintPlanStatus::act(Simulation &simulation) {
    if (simulation.getPlanCounter() < planId) {
        error ("Plan doesn't exist");
    }
    else {
        Plan p = simulation.getPlan(planId);
        cout << p.toString() << endl;
        complete();
    }
}
     PrintPlanStatus *PrintPlanStatus::clone() const {
        return new PrintPlanStatus(*this);
     }

     const string PrintPlanStatus::toString() const {
        return "planStatus " + planId + statusToString(getStatus());

     }

//***********************************************************************************************************

//************************************************ ChangePlanPolicy ************************************************

//Constractor
 ChangePlanPolicy::ChangePlanPolicy(const int planId, const string &newPolicy) : planId(planId), newPolicy(newPolicy) {}

void ChangePlanPolicy::act(Simulation &simulation) {
    if (simulation.getPlanCounter() < planId || simulation.getPlan(planId).getSelectionPolicy() ==  newPolicy) {
        error ("Cannot change selection policy")
    }
    else {
        Plan currentPlan = simulation.getPlan(planId);
        currentPlan.setSelectionPolicy(getSelectionPolicy(newPolicy), currentPlan.getlifeQualityScore(), currentPlan.getEconomyScore(), currentPlan.getEnvironmentScore())
    }
}




