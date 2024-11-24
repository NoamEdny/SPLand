#include "SelectionPolicy.h"
#include <climits> 

//***********************************************************************************************************

//************************************************  NaiveSelection ************************************************

//Constrector:
NaiveSelection::NaiveSelection() : lastSelectedIndex(-1) {}


// Ruls Of 3:

// Copy-Constrector:
NaiveSelection:: NaiveSelection(NaiveSelection &other) : lastSelectedIndex(other.lastSelectedIndex) {}


//Destructor:
NaiveSelection::~NaiveSelection() override{
    delete NaiveSelection;
}


//Methods:

//selectFacility:
const FacilityType& NaiveSelection::selectFacility(const std::vector<FacilityType>& facilitiesOptions) {
    lastSelectedIndex = (lastSelectedIndex + 1) % facilitiesOptions.size();
    return facilitiesOptions[lastSelectedIndex];
}
//toString:
const string NaiveSelection::toString() const override{
    return "Naive";
}

//clone
NaiveSelection::NaiveSelection *clone() const override{
    return new NaiveSelection(*this);
}

//***********************************************************************************************************

//************************************************  BalancedSelection ************************************************

//Constractor
BalancedSelection::BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore) :
 LifeQualityScore(LifeQualityScore), EconomyScore(EconomyScore), EnvironmentScore(EnvironmentScore) {}

// Ruls Of 3:

// Copy constactor
BalancedSelection::BalancedSelection(BalancedSelection &other) : LifeQualityScore(other.LifeQualityScore), EconomyScore(other.EconomyScore), EnvironmentScore(other.EnvironmentScore) {}

//Destructor:
BalancedSelection::~BalancedSelection() override{
    delete BalancedSelection;
}

//Methods:

//selectFacility:
const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override {
     // Start with a very large initial value to find the minimum difference
    int minDifference = INT_MAX; 
    int selectedIndex = 0;
    // Iterate over all available facilities
    for (size_t i = 0; i < facilitiesOptions.size(); ++i) {
        const FacilityType& facility = facilitiesOptions[i];
         // Calculate the new scores after adding the current facility's impact
        int newLifeQuality = LifeQualityScore + facility.getLifeQualityScore();
        int newEconomy = EconomyScore + facility.getEconomyScore();
        int newEnvironment = EnvironmentScore + facility.getEnvironmentScore();

    1   // Determine the maximum and minimum scores after adding the facility
        int maxScore = std::max({newLifeQuality, newEconomy, newEnvironment});
        int minScore = std::min({newLifeQuality, newEconomy, newEnvironment});
        int difference = maxScore - minScore;

         // Update the selected index if this facility provides a smaller difference
        if (difference < minDifference) {
            minDifference = difference;
            selectedIndex = i;
        }
    }
    // Return the facility with the smallest difference in scores
    return facilitiesOptions[selectedIndex];
}

//toString:
const string toString() const override {
    return "Balanced";
}

//clone:
BalancedSelection *clone() const override {
    return new BalancedSelection(*this);
}


//***********************************************************************************************************
//************************************************  EconomySelection ************************************************

//Constractor
EconomySelection::EconomySelection() : lastSelectedIndex(-1) {}

// Ruls Of 3:

//Copy constractor
EconomySelection::EconomySelection(EconomySelection &other) : lastSelectedIndex(other.lastSelectedIndex) {}

//Destructor:
~EconomySelection() override{
    delete EconomySelection;
}

//Methods:
//selectFacility:
const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override{


    // Iterate over the facilities in a circular manner, starting from the next index
    for (size_t i = 1; i <= facilitiesOptions.size(); ++i) {
        size_t index = (lastSelectedIndex + i) % facilitiesOptions.size(); 
        // Check if the facility belongs to the ECONOMY category
        if (facilitiesOptions[index].getCategory() == FacilityCategory::ECONOMY) {
            lastSelectedIndex = index; 
            return facilitiesOptions[index]; 
        }
    }
    // If no facility matches, throw an exception
    //throw std::runtime_error("No ECONOMY facility found.");
}

//toString
 const string EconomySelection::toString() const override {
    return "Economy";
}

//clone
EconomySelection::EconomySelection *clone() const override {
    return new EconomySelection(*this);
}



class SustainabilitySelection: public SelectionPolicy {
    //Constractor
 SustainabilitySelection::SustainabilitySelection() : lastSelectedIndex(-1) {}
//Copy constractor
SustainabilitySelection::SustainabilitySelection(SustainabilitySelection &other) : lastSelectedIndex(other.lastSelectedIndex) {}


const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override{
        // Iterate over the facilities in a circular manner, starting from the next index
     for (size_t i = 1; i <= facilitiesOptions.size(); ++i) {
        size_t index = (lastSelectedIndex + i) % facilitiesOptions.size(); 
                // Check if the facility belongs to the ECONOMY category
        if (facilitiesOptions[index].getCategory() == FacilityCategory::ECONOMY) {
            lastSelectedIndex = index; 
            return facilitiesOptions[index]; 
        }
}

 const string toString() const override{
    return "Sustainability";
}

SustainabilitySelection *clone() const override{
    return new SustainabilitySelection(*this);
    
}  
~SustainabilitySelection() override{
    delete SustainabilitySelection;
}
}









