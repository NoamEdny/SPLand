#include "Action.h"



//SimulateStep

//Constracot
SimulateStep::SimulateStep(const int numOfSteps) : numOfSteps(numOfSteps) {}

SimulateStep::SimulateStep(const int numOfSteps) : numOfSteps(1) {}

//Copy constractor
SimulateStep::SimulateStep(const SimulateStep &other) : numOfSteps(other.numOfSteps) {}

void SimulateStep::act(Simulation &simulation) {
    for (simulation.getPlan : )
 }