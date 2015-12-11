//
// Created by Tom Macmichael on 19/11/2015.
//
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

#ifndef CSLP_PASSENGER_H
#define CSLP_PASSENGER_H

#include "minibus.h"
#include "request.h"

struct Passenger {
    struct Minibus currentBus;
    struct Request *request;
};

struct Passenger *Passenger_create();
struct Request* Passenger_make_request(struct Passenger *passenger, int noStops);
void Passenger_destroy(struct Passenger *passenger);
void Passenger_disembark(struct Passenger *passenger, struct Minibus *minibus);
void Passenger_embark(struct Passenger *passenger, struct Minibus *minibus);

#endif //CSLP_PASSENGER_H
