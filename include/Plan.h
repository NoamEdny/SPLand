#pragma once
#include <vector>
#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
using std::vector;

enum class PlanStatus {
    AVALIABLE,
    BUSY,
};

class Plan {
    public:
    //Constructor
        Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions);

    //Rule Of 3:
        // Copy-Constructor
        Plan(const Plan &other);
        //vector<Facility*>* cloneFacilitys(const vector<Facility*> &other);

        // Copy Assignment Operator
        Plan operator=(const Plan &other) const;
        
        // Destructor
        ~Plan();
    //Methodes:
        //geters:
        const int getlifeQualityScore() const;
        const int getEconomyScore() const;
        const int getEnvironmentScore() const;
        const vector<Facility*> &getFacilities() const;

        void setSelectionPolicy(SelectionPolicy *selectionPolicy);
        void step();
        void printStatus();
        void addFacility(Facility* facility);
        const string toString() const;
        string statusToString() const;

    private:
        int plan_id;
        Settlement &settlement;
        SelectionPolicy *selectionPolicy; // the size of ths instence of SelectionPolicy in unknow
        PlanStatus status;
        int capacity; //the capacity of Facility that can be build
        vector<Facility*> facilities;
        vector<Facility*> underConstruction;
        const vector<FacilityType> &facilityOptions;
        int life_quality_score, economy_score, environment_score;
};