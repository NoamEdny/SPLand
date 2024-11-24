#include "Facility.h"
#include <iostream>


//************************************************  FacilityType ************************************************
//Constrector:
FacilityType:: FacilityType(const string &name, const FacilityCategory category,
 const int price, const int lifeQuality_score, const int economy_score, const int environment_score):
name(name), category(category) , price(price), lifeQuality_score(lifeQuality_score),
 economy_score(economy_score), environment_score(environment_score)
{}

// Ruls Of 3:

// Copy-Constrector:
FacilityType:: FacilityType(FacilityType &other) :
name(other.getName()), category(other.getCategory()) , price(other.getCost()), lifeQuality_score(other.getLifeQualityScore()),
 economy_score(other.getEconomyScore()), environment_score(other.getEnvironmentScore())
 {}

// 

//Methods:
const string &FacilityType::getName() const {
    return name;
}


int FacilityType::getCost() const {
    return price;
}

int FacilityType::getLifeQualityScore() const {
    return lifeQuality_score;
}

int FacilityType::getEnvironmentScore() const {
    return environment_score;
}

int FacilityType::getEconomyScore() const {
    return economy_score;
}

FacilityCategory FacilityType::getCategory() const {
    return category;
}
//***********************************************************************************************************

//************************************************  Facility ************************************************

//Constrectors:
Facility::Facility(const string &name, const string &settlementName, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score):
FacilityType(name, category, price, lifeQuality_score, economy_score, environment_score), 
 settlementName(settlementName),timeLeft(price),
  status(FacilityStatus::UNDER_CONSTRUCTIONS) // defult state of status is UNDER_CONSTRUCTIONS = 0
{}

Facility:: Facility(FacilityType &type, const string &settlementName):
FacilityType(type), settlementName(settlementName), timeLeft(type.getCost()),
status(FacilityStatus::UNDER_CONSTRUCTIONS) // defult state of status is UNDER_CONSTRUCTIONS = 0
 {}

// Ruls Of 3:

// Copy-Constrector:
Facility::Facility(Facility &other):
FacilityType(other), settlementName(other.getSettlementName()),timeLeft(other.getTimeLeft()), status(other.getStatus())
{}

//Methods:

const string &Facility::getSettlementName() const {
    return settlementName;
}

const int Facility::getTimeLeft() const {
    return timeLeft;
}

FacilityStatus Facility::step(){
    FacilityStatus status = getStatus();
    if (status == FacilityStatus::UNDER_CONSTRUCTIONS){
    timeLeft -= 1;
    }
    if (timeLeft == 0){
        setStatus(FacilityStatus:: OPERATIONAL);
    }
    return status;
}
void Facility::setStatus(FacilityStatus status) {
    this->status = status;
}

const FacilityStatus &Facility::getStatus() const {
    return status;
}

const string Facility::toString() const {
    // FacilityStatus To String:
    string statusString = "UNKNOWN_STATUS";
    switch (this->getStatus()) {
        case FacilityStatus::UNDER_CONSTRUCTIONS:
            statusString = "UNDER_CONSTRUCTIONS";
            break;
        case FacilityStatus::OPERATIONAL:
            statusString = "OPERATIONAL";
            break;

    }

    std::string timeToString = std::to_string(this->getTimeLeft());

    const string toString = "name: " + this->getName() + ", settlement name: " + this->getSettlementName() +
    ", status: "+ statusString +", time left: "+ timeToString;
    return toString;
}



