//
// Created by Tom Macmichael on 19/11/2015.
//

#include "request.h"

unsigned int rand_interval(unsigned int min, unsigned int max)
{
    int r;
    const unsigned int range = 1 + max - min;
    const unsigned int buckets = RAND_MAX / range;
    const unsigned int limit = buckets * range;

    /* Create equal size buckets all in a row, then fire randomly towards
     * the buckets until you land in one of them. All buckets are equally
     * likely. If you land off the end of the line of buckets, try again. */
    do
    {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}

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
    printf("-> new request placed from stop %d to stop %d for departure at %d scheduled \n", request->startStop, request->destinationStop, request->desiredBoardingTime);
}

/**
 * Generates a random request
 * @param numberOfBusStops
 * @return Request*
 */
Request* Request_random(int numberOfBusStops) {

    // Generates a number between 0 and the largest bus stop number (numberOfBusStops)
    unsigned int max = (unsigned int) numberOfBusStops-1;
    int startStop = rand_interval(0, max);
    int destinationStop = rand_interval(0, numberOfBusStops);

    // Generates a random boarding time
    int desiredBoardingTime = 0000;

    return Request_create(startStop, destinationStop, desiredBoardingTime);
}