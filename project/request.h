//
// Created by Tom Macmichael on 16/12/2015.
//

#ifndef CSLP_REQUEST_H
#define CSLP_REQUEST_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <minibus.h>
#include "simulation.h"

#include <math.h>
#ifdef NAN
/* NAN is supported */
#endif
#ifdef INFINITY
/* INFINITY is supported */
#endif

typedef struct Request {
    int startStop;
    int destinationStop;
    int desiredBoardingTime;
    Minibus *minibus;
} Request;

Request *Request_create(int startStop, int destinationStop, int desiredBoardingTime);
void Request_destroy(Request *request);
void Request_print(Request *request);
Request* Request_random(Simulation *simulation);


void Passenger_disembark(Request *request, Minibus *minibus);
void Passenger_embark(Request *request, Minibus *minibus);

#endif //CSLP_REQUEST_H
