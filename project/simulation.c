//
// Created by Tom Macmichael on 24/11/2015.
//

#include "simulation.h"

/*
 * Possible events:
 * - new passenger request
 * - arrival at a bus stop
 * - disembarkation of a passenger
 * - boarding of a new passenger
 */

void Simulation_start(struct ParsedFile *pf)
{
    // There's a fixed amount of minibuses in the system, let's make these first and store in array
    struct Minibus * minibuses = createMinibuses(pf);

    // Print our minibuses
    Minibus_print(&minibuses[4]);
    Minibus_print(&minibuses[3]);
    Minibus_print(&minibuses[2]);
    Minibus_print(&minibuses[1]);
    Minibus_print(&minibuses[0]);

    // Our simulation algorithm, boom
    for (int currentTime = 0; currentTime <= pf->stopTime; currentTime++)
    {
        // Convert request rate in seconds
        int requestRate = (int) pf->requestRate*60;

        // We only want to create a request with the request rate...
        if (currentTime % requestRate == 0)
        {
            // Make a new (random) request
            struct Passenger* passenger = Passenger_create();
            struct Request* request = Passenger_make_request(passenger, pf->noStops);
            Request_print(request);
            //Request_destroy(request);
            //Passenger_destroy(passenger);
        }
    }

    // Free up the memory

}

struct Minibus * createMinibuses(struct ParsedFile *pf)
{
    // Create an array of pointers to the minibuses that we've created
    struct Minibus *minibuses = malloc(pf->noBuses * sizeof(struct Minibus*));
    for (int total = 0; total < pf->noBuses; total++)
    {
        minibuses[total] = *Minibus_create(0, 0, pf->busCapacity, pf->boardingTime);
    }
    return minibuses;
}

