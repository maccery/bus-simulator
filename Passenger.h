//
// Created by Tom Macmichael on 19/11/2015.
//

#ifndef CSLP_PASSENGER_H
#define CSLP_PASSENGER_H

#include "minibus.h"
#include "request.h"

struct Passenger {
    struct Minibus currentBus;
    struct Request request;
};

#endif //CSLP_PASSENGER_H
