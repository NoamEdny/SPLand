# include "Plan.h"
// check the consractor (ettlement(const_cast<Settlement&>(settlement)))
Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions) 
: plan_id(planId), settlement(const_cast<Settlement&>(settlement)), selectionPolicy(selectionPolicy), facilityOptions(facilityOptions),
life_quality_score(0), economy_score(0), environment_score(0) {}

const int Plan::getlifeQualityScore() const {
    return life_quality_score;
}

const int Plan::getEconomyScore() const {
    return economy_score;
}

const int Plan::getEnvironmentScore() const {
    return environment_score;
}

void Plan:: setSelectionPolicy(SelectionPolicy *selectionPolicy) {
    this->selectionPolicy = selectionPolicy;
}

void Plan::step() {
    
}

