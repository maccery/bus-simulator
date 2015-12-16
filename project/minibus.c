//
// Created by Tom Macmichael on 19/11/2015.
//

#include "minibus.h"
#include "passenger.h"

Minibus *Minibus_create(int currentStop, int occupancy, int capacity, int boardingTime) {
    // Allocate enough memory to create a new struct and check we have enough memory
    Minibus *minibus = malloc(sizeof(Minibus));
    assert(minibus != NULL);

    minibus->currentStop = currentStop;
    minibus->occupancy = occupancy;
    minibus->capacity = capacity;
    minibus->boardingTime = boardingTime;

    return minibus;
}

void Minibus_destroy(Minibus *minibus) {
    assert(minibus != NULL);
    free(minibus);
}

void Minibus_print(Minibus *minibus) {
    printf("MINIBUS PRINT. Bus capacity: %d\n", minibus->capacity);
}