//
// Created by Tom Macmichael on 16/12/2015.
//
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

#ifndef CSLP_REQUEST_H
#define CSLP_REQUEST_H

typedef struct Request {
    int startStop;
    int destinationStop;
    int desiredBoardingTime;
} Request;

Request *Request_create(int startStop, int destinationStop, int desiredBoardingTime);
void Request_destroy(Request *request);
void Request_print(Request *request);
Request* Request_random(int numberOfBusStops);

#endif //CSLP_REQUEST_H
