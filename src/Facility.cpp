#include "Facility.h"
#include <string>
#include <vector>
#include <iostream>
using std::string;
using std::vector;
using namespace std;
//***********************************************************************************************************

//************************************************  FacilityType ************************************************

//Constrectors:
FacilityType::FacilityType(const string &name, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score)
: name(name), category(category), price(price), lifeQuality_score(lifeQuality_score),
 economy_score(economy_score), environment_score(environment_score){}

FacilityType::FacilityType()
: FacilityType("", FacilityCategory::LIFE_QUALITY, 0, 0, 0, 0){}

//Rule Of 3:
FacilityType::FacilityType(const FacilityType &other)
:FacilityType(other.name, other.category, other.price, other.lifeQuality_score,other.economy_score,other.environment_score){}

FacilityType &FacilityType::operator=(const FacilityType &other){
    return *this;
}

FacilityType::~FacilityType(){

}

//Method
bool FacilityType::operator==(const FacilityType &other) const {
    return (name == other.name) && (category == other.category) && 
           (price == other.price) &&
           (lifeQuality_score == other.lifeQuality_score) &&
           (economy_score == other.economy_score);
}


const string &FacilityType::getName() const{
    return name;
}

int FacilityType::getCost() const{
    return price;
}

int FacilityType::getLifeQualityScore() const{
    return lifeQuality_score;
}

int FacilityType::getEnvironmentScore() const{
    return environment_score;
}

int FacilityType::getEconomyScore() const{
    return economy_score;
}

FacilityCategory FacilityType::getCategory() const{
    return category;
}

//***********************************************************************************************************

//************************************************  Facility ************************************************

//Constrectors:
Facility::Facility(const string &name, const string &settlementName, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score)
    : FacilityType(name, category, price, lifeQuality_score, economy_score, environment_score),
    settlementName(settlementName),
    status(FacilityStatus::UNDER_CONSTRUCTIONS),
    timeLeft(price){}

Facility::Facility(const FacilityType &type, const string &settlementName)
    :Facility(type.FacilityType::getName(), settlementName, type.FacilityType::getCategory(), 
    type.FacilityType::getCost(), type.FacilityType::getLifeQualityScore(), type.FacilityType::getEconomyScore(),
     type.FacilityType::getEnvironmentScore()){}

Facility::Facility()
: Facility(FacilityType(), ""){}

//Rule Of 3:
Facility::Facility(const Facility &other)
:Facility(other.name, other.settlementName,other.category, other.price, other.lifeQuality_score,other.economy_score,other.environment_score){}

Facility &Facility::operator=(const Facility &other){
    return *this;
}

Facility::~Facility(){}

//Method:

const string &Facility::getSettlementName() const{
    return settlementName;
}

const int Facility::getTimeLeft() const{
    return timeLeft;
}

FacilityStatus Facility::step(){
    if(timeLeft>0){
        timeLeft = timeLeft-1;
        if(timeLeft==0) {
        //cout << "hiiii" << endl;
        setStatus(FacilityStatus::OPERATIONAL);
        }
    }
    return status;
}

void Facility::setStatus(FacilityStatus status){
    this->status=status;
}

const FacilityStatus& Facility::getStatus() const{
    return status;
}



const string Facility::toString() const{
    return "facilityName: " + getName() + " , facilityStatus: " + statusToString();
}

string Facility::statusToString() const{
    string result;

    // Convert SettlementType to string
    switch (status) {
        case FacilityStatus::UNDER_CONSTRUCTIONS :
            result = "UNDER_CONSTRUCTIONS";
            break;
        case FacilityStatus::OPERATIONAL:
            result = "OPERATIONAL";
            break;

    }

    return result;
}