//
// Created by Tom Macmichael on 19/11/2015.
//

#include "passenger.h"

struct Passenger *Passenger_create() {
    // Allocate enough memory to create a new struct and check we have enough memory
    struct Passenger *passenger = malloc(sizeof(struct Passenger));
    assert(passenger != NULL);
    return passenger;
}

void Passenger_print(struct Passenger *passenger) {
    printf("-> Passenger is on the bus %d, going from stop %d to stop %d", passenger->currentBus.id, passenger->request.startStop, passenger->request.destinationStop);
    printf("\n");
}

void Passenger_destroy(struct Passenger *passenger) {
    assert(passenger != NULL);
    free(passenger);
}

void Passenger_disembark(struct Passenger *passenger, struct Minibus *minibus) {
    minibus->occupancy = minibus->occupancy-1;
    //passenger->currentBus = NULL;
    printf("-> Minibus disembaraked passenger at stop %d\n", minibus->currentStop);
    printf("-> Minibus occupancy changed to %d\n", minibus->occupancy);
}

void Passenger_embark(struct Passenger *passenger, struct Minibus *minibus) {
    minibus->occupancy = minibus->occupancy+1;
    passenger->currentBus = *minibus;
    printf("-> Minibus added passenger at stop %d\n", minibus->currentStop);
    printf("-> Minibus occupancy changed to %d\n", minibus->occupancy);
}