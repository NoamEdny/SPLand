#include "Settlement.h"

//Constrector:
Settlement:: Settlement(const string &name, SettlementType type) : name(name), type(type) {}

//De-Constrector: No need for De-Constrector 


const string &Settlement:: getName() const{
    return name;
}

SettlementType Settlement:: getType() const
{
    return type;
}

const string Settlement:: toString() const
{
    string result = "Settlement Name: " + name + ", Type: ";

    // Convert SettlementType to string
    switch (type) {
        case SettlementType::VILLAGE:
            result += "VILLAGE";
            break;
        case SettlementType::CITY:
            result += "CITY";
            break;
        case SettlementType::METROPOLIS:
            result += "METROPOLIS";
            break;
    }

    return result;
}

