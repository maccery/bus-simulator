//
// Created by Tom Macmichael on 19/11/2015.
//

#include "passenger.h"

struct Passenger *Passenger_create(struct Minibus currentBus, struct Request request) {
    // Allocate enough memory to create a new struct and check we have enough memory
    struct Passenger *passenger = malloc(sizeof(struct Passenger));
    assert(passenger != NULL);

    passenger->currentBus = currentBus;
    passenger->request = request;

    return passenger;
}

void Passenger_destroy(struct Passenger *passenger) {
    assert(passenger != NULL);
    free(passenger);
}

void Passenger_disembark(struct Passenger *passenger, struct Minibus *minibus) {
    minibus->occupancy = minibus->occupancy-1;
    passenger->currentBus = NULL;
}

void Passenger_embark(struct Passenger *passenger, struct Minibus *minibus) {
    minibus->occupancy = minibus->occupancy+1;
    passenger->currentBus = *minibus;
}