//
// Created by Tom Macmichael on 24/11/2015.
//

#include "simulation.h"
#include "dijkstra.h"

#include <time.h>

// We need a queue of events


// We need a callback struct
typedef void (*event_cb_t)(const struct event *evt, void *userdata);
int event_cb_register(event_cb_t cb, void *userdata);

struct eventCallBack {
    event_cb_t cb;
    void *data;
};


void delay(int milliseconds)
{
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}

static void my_event_cb(const struct event *evt, void *data)
{
    /* do stuff and things with the event */
}

/*
 * Possible events:
 * - new passenger request
 * - arrival at a bus stop
 * - disembarkation of a passenger
 * - boarding of a new passenger
 */
void findBus(struct ParsedFile *pf, struct Minibus * minibuses, struct Request* request, int currentTime)
{
    // Really large shortest journey time to start with
    int shortestJourneyTime = 50000000;
    struct Minibus* quickestBus;

    // loop through minibuses to find the best one for our user
    for (int i = 0; i <= pf->noBuses; i ++)
    {
        // Calculate the time for this minibus to get to that person
        struct Minibus* minibus = &minibuses[i];
        int journeyTime = makeDis(pf->map, pf->edgeCount, minibus->currentStop, request->startStop);

        // If it's not the shortest, ignore it
        if (journeyTime <= shortestJourneyTime)
        {
            quickestBus = minibus;
        }
    }

    // If the quickest time for the bus to get there, plus the travel time to destination is too late, we say so...
    int travelTime = makeDis(pf->map, pf->edgeCount, request->startStop, request->destinationStop);
    if (shortestJourneyTime + currentTime <= request->desiredBoardingTime)
    {
        printf("request cannot be accommodated\n");
    }
    else
    {
        printf("-> minibus %d is on its way! Gunna be there in %d mins ok c u then xx\n", quickestBus->id, travelTime);
        delay(5000);

        // We need to make a new event, with a callback function
        event_cb_register(my_event_cb, &my_custom_data);
    }
}

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

            // Now we need to do something with this request...
            // This will calculate the SHORTEST time (in minutes) for a bus to get here...
            findBus(pf, minibuses, request, currentTime);

            //Request_destroy(request);
            //Passenger_destroy(passenger);
        }

        // At this time t, are there any events?
        // If yes, we need to execute their callback function
        callback->cb(event, callback->data);

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

