//
// Created by Tom Macmichael on 24/11/2015.
//

#ifndef CSLP_SIMULATION_H
#define CSLP_SIMULATION_H

#include "parser.h"
#include "request.h"
#include "passenger.h"

typedef struct Simulation {
} Simulation;

void Simulation_start(ParsedFile *pf);
Minibus * createMinibuses(ParsedFile *pf);

#endif //CSLP_SIMULATION_H
