//
// Created by Tom Macmichael on 19/11/2015.
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

#ifndef CSLP_REQUEST_H
#define CSLP_REQUEST_H
struct Request {
    int startStop;
    int destinationStop;
    int desiredBoardingTime;
};

struct Request *Request_create(int startStop, int destinationStop, int desiredBoardingTime);
void Request_destroy(struct Request *request);
struct Request* Request_random(int numberOfBusStops);

#endif //CSLP_REQUEST_H
