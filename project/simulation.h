//
// Created by Tom Macmichael on 24/11/2015.
//

#ifndef CSLP_SIMULATION_H
#define CSLP_SIMULATION_H


#include "parser.h"
#include "minibus.h"
#include "statistics.h"

typedef struct Simulation {
    ParsedFile *pf;
    int currentTime;
    Minibus * minibuses;
} Simulation;



Simulation *Simulation_create(ParsedFile *pf);
Statistics* Simulation_start(Simulation *simulation);
Minibus * createMinibuses(ParsedFile *pf);

void makeRandomRequest();
void makeRequest(int time);
int makeRequestCallback(void *data);
int busArrivedAtDestination(void *data);
int busArrived(void *data);
#endif //CSLP_SIMULATION_H
