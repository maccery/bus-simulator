//
// Created by Tom Macmichael on 19/11/2015.
//

#ifndef CSLP_MINIBUS_H
#define CSLP_MINIBUS_H

struct Minibus {
    int id;
    int currentStop;
    int occupancy; // Current occupancy of the bus
    int capacity; // Maximum number of people the bus can have
    int boardingTime; // The time it takes to board the passenger
};

#endif //CSLP_MINIBUS_H
