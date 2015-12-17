//
// Created by Tom Macmichael on 19/11/2015.
//

#include "minibus.h"
#include "passenger.h"

Minibus *Minibus_create(int id, int currentStop, int occupancy, int capacity) {
    // Allocate enough memory to create a new struct and check we have enough memory
    Minibus *minibus = malloc(sizeof(Minibus));
    assert(minibus != NULL);

    minibus->id = id;
    minibus->currentStop = currentStop;
    minibus->occupancy = occupancy;
    minibus->capacity = capacity;

    return minibus;
}

void Minibus_destroy(Minibus *minibus) {
    assert(minibus != NULL);
    free(minibus);
}

void Minibus_print(Minibus *minibus) {
    printf("MINIBUS PRINT. ID: %d Bus capacity: %d/%d\n", minibus->id, minibus->occupancy, minibus->capacity);
}