//
// Created by Tom Macmichael on 19/11/2015.
//

#include "request.h"
#include "simulation.h"
#include "event.h"

/**
 * Creates a request struct
 */
Request *Request_create(int startStop, int destinationStop, int desiredBoardingTime) {
    // Allocate enough memory to create a new and check we have enough memory
    Request *request = malloc(sizeof(Request));
    assert(request != NULL);

    request->startStop = startStop;
    request->destinationStop = destinationStop;
    request->desiredBoardingTime = desiredBoardingTime;

    return request;
}

/**
 * Frees the memory of a given request struct
 */
void Request_destroy(Request *request) {
    assert(request != NULL);
    free(request);
}

/**
 * Simply prints out the details of a request
 */
void Request_print(Request *request) {
    printf("-> new request placed from stop %d to stop %d for departure at ", request->startStop, request->destinationStop);
    formatTime(request->desiredBoardingTime);
    printf("\n");

}


/**
 * Generates a random request
 * @param numberOfBusStops
 * @return Request*
 */
Request* Request_random(Simulation *simulation) {
    ParsedFile *pf = simulation->pf;


    // Generates a number between 0 and the largest bus stop number (numberOfBusStops)
    unsigned int max = (unsigned int) pf->noStops-1;

    int startStop = 0;
    int destinationStop = 0;
    while (startStop == destinationStop)
    {
        startStop = rand_interval(0, max);
        destinationStop = rand_interval(0, max);
    }

    // Generates a random boarding time
    int pickupInterval = exponentialRand(pf->pickupInterval);
    int desiredBoardingTime = simulation->currentTime + pickupInterval;

    return Request_create(startStop, destinationStop, desiredBoardingTime);
}