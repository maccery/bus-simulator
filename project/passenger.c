//
// Created by Tom Macmichael on 19/11/2015.
//

#include "passenger.h"

Passenger *Passenger_create() {
    // Allocate enough memory to create a new and check we have enough memory
    Passenger *passenger = malloc(sizeof(Passenger));
    assert(passenger != NULL);
    return passenger;
}

void Passenger_print(Passenger *passenger) {
    printf("\n");
}

void Passenger_destroy(Passenger *passenger) {
    assert(passenger != NULL);
    free(passenger);
}

Request* Passenger_make_request(Passenger *passenger, int noStops) {
    Request* request = Request_random(noStops);
    passenger->request = request;
//    request->passenger = *passenger;

    return request;
}

void Passenger_disembark(Passenger *passenger, Minibus *minibus) {
    minibus->occupancy = minibus->occupancy-1;
    //passenger->currentBus = NULL;
    printf("-> Minibus disembaraked passenger at stop %d\n", minibus->currentStop);
    printf("-> Minibus occupancy changed to %d\n", minibus->occupancy);
}

void Passenger_embark(Passenger *passenger, Minibus *minibus) {
    minibus->occupancy = minibus->occupancy+1;
    passenger->currentBus = *minibus;
    printf("-> Minibus added passenger at stop %d\n", minibus->currentStop);
    printf("-> Minibus occupancy changed to %d\n", minibus->occupancy);
}