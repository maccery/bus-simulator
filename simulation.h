//
// Created by Tom Macmichael on 24/11/2015.
//

#ifndef CSLP_SIMULATION_H
#define CSLP_SIMULATION_H

#include "parser.h"
#include "request.h"
#include "passenger.h"

struct Simulation {
};

void Simulation_start(struct ParsedFile *pf);
struct Minibus * createMinibuses(struct ParsedFile *pf);

#endif //CSLP_SIMULATION_H
