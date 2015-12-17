//
// Created by Tom Macmichael on 24/11/2015.
//

#ifndef CSLP_SIMULATION_H
#define CSLP_SIMULATION_H


#include "parser.h"
#include "minibus.h"

typedef struct Simulation {
    ParsedFile *pf;
    int currentTime;
} Simulation;

void formatTime(int seconds)
{
    int hours = seconds / 3600;
    int remainder = seconds % 3600;
    int minutes = remainder / 60;
    int secs = remainder % 60;

    printf("<%d:%d:%d>\n", hours, minutes, secs);
}

Simulation *Simulation_create(ParsedFile *pf);
void Simulation_start(Simulation *simulation);
Minibus * createMinibuses(ParsedFile *pf);

#endif //CSLP_SIMULATION_H
