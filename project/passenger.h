//
// Created by Tom Macmichael on 19/11/2015.
//


#ifndef CSLP_PASSENGER_H
#define CSLP_PASSENGER_H

#include "minibus.h"
#include "request.h"

typedef struct Passenger {
    Minibus currentBus;
    Request *request;
} Passenger;

Passenger *Passenger_create();
Request* Passenger_make_request(Passenger *passenger, int noStops);
void Passenger_destroy(Passenger *passenger);
void Passenger_disembark(Passenger *passenger, Minibus *minibus);
void Passenger_embark(Passenger *passenger, Minibus *minibus);

#endif //CSLP_PASSENGER_H
