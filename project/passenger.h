//
// Created by Tom Macmichael on 19/11/2015.
//


#ifndef CSLP_PASSENGER_H
#define CSLP_PASSENGER_H

#include "minibus.h"
#include "request.h"

typedef struct Passenger {
    Minibus *currentBus;
    Request *request;
} Passenger;

Passenger *Passenger_create();
Request* Passenger_make_request(Simulation *simulation);
void Passenger_destroy(Passenger *passenger);
void Passenger_disembark(Request *request, Minibus *minibus);
void Passenger_embark(Request *request, Minibus *minibus);

#endif //CSLP_PASSENGER_H
