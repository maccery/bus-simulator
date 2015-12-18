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
#include "parser.h"


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

#endif //CSLP_REQUEST_H
