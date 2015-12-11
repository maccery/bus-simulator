//
// Created by Tom Macmichael on 19/11/2015.
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

#ifndef CSLP_MINIBUS_H
#define CSLP_MINIBUS_H

struct Minibus {
    int id;
    int currentStop;
    int occupancy; // Current occupancy of the bus
    int capacity; // Maximum number of people the bus can have
    int boardingTime; // The time it takes to board the passenger
};


struct Minibus *Minibus_create(int currentStop, int occupancy, int capacity, int boardingTime);
void Minibus_destroy(struct Minibus *Minibus);
void Minibus_print(struct Minibus *Minibus);
struct Minibus* Minibus_random(int MinibusTime, int numberOfBusStops);

#endif //CSLP_MINIBUS_H
