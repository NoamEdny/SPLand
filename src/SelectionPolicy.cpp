#include "SelectionPolicy.h"
#include <climits> 


// NaiveSelection
class NaiveSelection: public SelectionPolicy {
NaiveSelection::NaiveSelection() : lastSelectedIndex(-1) {}

//Copy constractor
NaiveSelection:: NaiveSelection(NaiveSelection &other) : lastSelectedIndex(other.lastSelectedIndex) {}


const FacilityType& NaiveSelection::selectFacility(const std::vector<FacilityType>& facilitiesOptions) {
    lastSelectedIndex = (lastSelectedIndex + 1) % facilitiesOptions.size();
    return facilitiesOptions[lastSelectedIndex];
}

const string toString() const override{
    return "Naive";
}
NaiveSelection *clone() const override{
    return new NaiveSelection(*this);
    }

~NaiveSelection() override{
    delete NaiveSelection;
}
}


//BalancedSelection
class BalancedSelection: public SelectionPolicy {
    //Constractor
BalancedSelection::BalancedSelection() : LifeQualityScore(LifeQualityScore), EconomyScore(EconomyScore), EnvironmentScore(EnvironmentScore) {}

// Copy constactor
BalancedSelection::BalancedSelection() : (BalancedSelection &other) : LifeQualityScore(other.LifeQualityScore), EconomyScore(other.EconomyScore), EnvironmentScore(other.EnvironmentScore) {}

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

const string toString() const override {
    return "Balanced";
}

BalancedSelection *clone() const override {
    return new BalancedSelection(*this);
}

~BalancedSelection() override{
    delete BalancedSelection;
}

}
class EconomySelection: public SelectionPolicy {
//Constractor
EconomySelection::EconomySelection() : lastSelectedIndex(-1) {}

//Copy constractor
EconomySelection::EconomySelection(EconomySelection &other) : lastSelectedIndex(other.lastSelectedIndex) {}

const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override;
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

 const string toString() const override {
    return "Economy";
 }

EconomySelection *clone() const override {
    return new EconomySelection(*this);
}

~EconomySelection() override{
    delete EconomySelection;
}

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









