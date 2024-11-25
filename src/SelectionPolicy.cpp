#include "SelectionPolicy.h"
#include <climits> 
#include <string>
using std::string;
using std::vector;
using std::max;
using std::min;


//***********************************************************************************************************

//************************************************  NaiveSelection ************************************************

//Constrector:
NaiveSelection::NaiveSelection() : lastSelectedIndex(-1) {}


// Ruls Of 3:

// Copy-Constrector:
NaiveSelection:: NaiveSelection(const NaiveSelection &other) : lastSelectedIndex(other.lastSelectedIndex) {}



//Copy -Opretor:

//Methods:

//selectFacility:
const FacilityType& NaiveSelection::selectFacility(const std::vector<FacilityType>& facilitiesOptions) {
    lastSelectedIndex = (lastSelectedIndex + 1) % facilitiesOptions.size();
    return facilitiesOptions[lastSelectedIndex];
}
//toString:
const string NaiveSelection::toString() const{
    return "Naive";
}

//clone
NaiveSelection* NaiveSelection::clone() const {
    return new NaiveSelection(*this);
}


//***********************************************************************************************************

//************************************************  BalancedSelection ************************************************

//Constractor
BalancedSelection::BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore) :
 LifeQualityScore(LifeQualityScore), EconomyScore(EconomyScore), EnvironmentScore(EnvironmentScore) {}

// Ruls Of 3:

// Copy constactor
BalancedSelection::BalancedSelection(const BalancedSelection &other) :
 LifeQualityScore(other.LifeQualityScore), EconomyScore(other.EconomyScore), EnvironmentScore(other.EnvironmentScore) {}

//Destructor:
/*BalancedSelection::~BalancedSelection() 
{}*/


//Methods:

//selectFacility:
const FacilityType& BalancedSelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
    int minDifference = INT_MAX; 
    int selectedIndex = 0;

    for (size_t i = 0; i < facilitiesOptions.size(); ++i) {
        const FacilityType& facility = facilitiesOptions[i];

        int newLifeQuality = LifeQualityScore + facility.getLifeQualityScore();
        int newEconomy = EconomyScore + facility.getEconomyScore();
        int newEnvironment = EnvironmentScore + facility.getEnvironmentScore();

        int maxScore = std::max(newLifeQuality, std::max(newEconomy, newEnvironment));
        int minScore = std::min(newLifeQuality, std::min(newEconomy, newEnvironment));
        int difference = maxScore - minScore;

        if (difference < minDifference) {
            minDifference = difference;
            selectedIndex = i;
        }
    }

    return facilitiesOptions[selectedIndex];
}


//toString:
const string BalancedSelection::toString() const {
    return "Balanced";
}

//clone:
BalancedSelection* BalancedSelection::clone() const {
    return new BalancedSelection(*this);
}


//***********************************************************************************************************
//************************************************  EconomySelection ************************************************

//Constractor
EconomySelection::EconomySelection() : lastSelectedIndex(-1) {}

// Ruls Of 3:
//Copy constractor
EconomySelection::EconomySelection(const EconomySelection &other) : lastSelectedIndex(other.lastSelectedIndex) {}


//Methods:
//selectFacility:
const FacilityType& EconomySelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {


    // Iterate over the facilities in a circular manner, starting from the next index
    for (size_t i = 1; i <= facilitiesOptions.size(); ++i) {
        size_t index = (lastSelectedIndex + i) % facilitiesOptions.size(); 
        // Check if the facility belongs to the ECONOMY category
        if (facilitiesOptions[index].getCategory() == FacilityCategory::ECONOMY) {
            lastSelectedIndex = index; 
            return facilitiesOptions[index]; 
        }
    }
}

//toString
 const string EconomySelection::toString() const {
    return "Economy";
}

//clone
EconomySelection* EconomySelection :: clone() const {
    return new EconomySelection(*this);
}

//***********************************************************************************************************
//************************************************  SustainabilitySelectio ************************************************

    
//Constractor
 SustainabilitySelection::SustainabilitySelection() : lastSelectedIndex(-1) {}

// Ruls Of 3:
//Copy constractor
SustainabilitySelection::SustainabilitySelection(const SustainabilitySelection &other) : lastSelectedIndex(other.lastSelectedIndex) {}


//Methods:
//selectFacility:
const FacilityType& SustainabilitySelection::selectFacility(const vector<FacilityType>& facilitiesOptions){
        // Iterate over the facilities in a circular manner, starting from the next index
     for (size_t i = 1; i <= facilitiesOptions.size(); ++i) {
        size_t index = (lastSelectedIndex + i) % facilitiesOptions.size(); 
                // Check if the facility belongs to the ECONOMY category
        if (facilitiesOptions[index].getCategory() == FacilityCategory::ECONOMY) {
            lastSelectedIndex = index; 
            return facilitiesOptions[index]; 
        }
    }
}
//toString

const string SustainabilitySelection::toString() const {
    return "Sustainability";
}


//clone:
SustainabilitySelection* SustainabilitySelection :: clone() const {
    return new SustainabilitySelection(*this);
}










