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

Request* Passenger_make_request(Simulation *simulation) {
    Request* request = Request_random(simulation);
    //passenger->request = request;
//    request->passenger = *passenger;

    return request;
}

void Passenger_disembark(Request *request, Minibus *minibus) {
    minibus->occupancy = minibus->occupancy-1;
    minibus->currentStop = request->destinationStop;
    //passenger->currentBus = NULL;
    printf("-> Minibus %d disembaraked passenger at stop %d. ", minibus->id, request->destinationStop);
    printf(" Minibus %d occupancy changed to %d\n",  minibus->id, minibus->occupancy);
}

void Passenger_embark(Request *request, Minibus *minibus) {
    minibus->currentStop = request->startStop;
    //minibus->occupancy = minibus->occupancy+1;
    printf("-> Minibus %d added passenger at stop %d. ", minibus->id, request->startStop);
    printf("-> Minibus %d occupancy changed to %d\n", minibus->id, minibus->occupancy);
}