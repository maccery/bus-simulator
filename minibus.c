//
// Created by Tom Macmichael on 19/11/2015.
//

#include "minibus.h"
#include "passenger.h"

struct Minibus *Minibus_create(int currentStop, int occupancy, int capacity, int boardingTime) {
    // Allocate enough memory to create a new struct and check we have enough memory
    struct Minibus *minibus = malloc(sizeof(struct Minibus));
    assert(minibus != NULL);

    minibus->currentStop = currentStop;
    minibus->occupancy = occupancy;
    minibus->capacity = capacity;
    minibus->boardingTime = boardingTime;

    return minibus;
}

void Minibus_destroy(struct Minibus *minibus) {
    assert(minibus != NULL);
    free(minibus);
}

void Minibus_print(struct Minibus *minibus) {
    printf("MINIBUS PRINT. Bus capacity: %d\n", minibus->capacity);
}