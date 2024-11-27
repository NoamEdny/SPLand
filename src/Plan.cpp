# include "Plan.h"
#include <iostream>
using std::vector;
using std::string;
using namespace std;


// check the consractor (ettlement(const_cast<Settlement&>(settlement)))
Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions) 
: 
plan_id(planId), settlement(const_cast<Settlement&>(settlement)), selectionPolicy(selectionPolicy->clone()), facilityOptions(facilityOptions), //from user
status(PlanStatus::AVALIABLE), capacity(settlement.getCapacity()), //status
facilities(), underConstruction(),//facility
life_quality_score(0), economy_score(0), environment_score(0) {} //scores

//Rule Of 3:
// Copy-Constructor
Plan::Plan(const Plan &other)
//Initialize the const variables before the default constructor in C++
:Plan(other.plan_id, other.settlement, selectionPolicy->clone(),other.facilityOptions)
{
    status = other.status;
    capacity = other.capacity;
    life_quality_score = other.getlifeQualityScore();
    economy_score = other.getEconomyScore();
    environment_score = other.getEnvironmentScore();

    //Deep Copy of the Facility lists:
    for(Facility* facility : other.underConstruction){
        addFacility(new Facility(*facility));
    }

    for(Facility* facility : other.facilities){
        addFacility(new Facility(*facility));
    }
}

// Copy Assignment Operator
Plan Plan::operator=(const Plan &other) const{
    
}

//Destructor
Plan::~Plan(){
    delete selectionPolicy;
    for (Facility* facility : facilities) {
        delete facility;
    }
    for (Facility* facility : underConstruction) {
        delete facility;
    }

}


//Methods:
//geters:
const int Plan::getlifeQualityScore() const {
    return life_quality_score;
}

const int Plan::getEconomyScore() const {
    return economy_score;
}

const int Plan::getEnvironmentScore() const {
    return environment_score;
}

const vector<Facility*> &Plan::getFacilities() const {
    return facilities;
}

// Other methods:
void Plan::setSelectionPolicy(SelectionPolicy *newPolicy) {
    if (selectionPolicy) { 
        delete selectionPolicy; 
    }  
        selectionPolicy = newPolicy->clone(); 

}


void Plan::step() {
    // select Facility acording to the capacity and the selectionPolicy
    while(status == PlanStatus::AVALIABLE){
        FacilityType next = selectionPolicy->selectFacility(facilityOptions);
        Facility* nextFacility = new Facility(next, settlement.getName());// nextFacility is in the heap because we need it after the scope of "step()"
        addFacility(nextFacility);
        capacity = capacity -1;
        if (capacity == 0)
        {
            status = PlanStatus::BUSY;
        }    
    }
    // Build the facilitys:
    if (status == PlanStatus::BUSY)
    {
        for (auto it = underConstruction.begin(); it != underConstruction.end(); ) {
        Facility* facilityToBuild = *it;
        FacilityStatus newStatus = facilityToBuild->step();
        if (newStatus == FacilityStatus::OPERATIONAL) {
            addFacility(facilityToBuild);
            it = underConstruction.erase(it); // delete the arry element (no need to delete facilityToBuild becsue it's in facilities)
        } else {
            ++it; // iteret to the next element
        }
    }
    } 
}

void Plan::addFacility(Facility* facility){
    if(facility->getStatus() == FacilityStatus::OPERATIONAL){
            facilities.push_back(facility);
    }
    else{
        underConstruction.push_back(facility);
    }  
}

void Plan::printStatus(){
    string statusString;
    switch (status) {
        case PlanStatus::AVALIABLE:
            statusString =  "AVALIABLE";
            break;
        case PlanStatus::BUSY:
            statusString = "BUSY";
            break;
    }
    cout << statusString << endl;
}


const string Plan::toString() const {
    string output;
    output = "ID: " + std::to_string(plan_id) + "\n" + 
             "Plan Status: " + statusToString() + "\n" +
             "Settlement Name: " + settlement.getName();

    return output;
}

string Plan::statusToString() const{
    string statusString;
    switch (status) {
        case PlanStatus::AVALIABLE:
            statusString =  "AVALIABLE";
            break;
        case PlanStatus::BUSY:
            statusString = "BUSY";
            break;
    }
    return statusString;
}


