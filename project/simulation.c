//
// Created by Tom Macmichael on 24/11/2015.
//

#include <stdbool.h>
#include "simulation.h"
#include "dijkstra.h"
#include "event.h"
#include "passenger.h"


// Handles the situation when bus arrived
int busArrived(void *data) {

    Request *request = (Request*) data;
    Passenger_embark(request, request->minibus);
    return 5;
}


// Global eventqueue
EventQueue *eventQueue = NULL;

/*
 * Possible events:
 * - new passenger request
 * - arrival at a bus stop
 * - disembarkation of a passenger
 * - boarding of a new passenger
 */
void findBus(ParsedFile *pf, Minibus * minibuses, Passenger* passenger, int currentTime)
{
    Request *request = passenger->request;

    // Really large shortest journey time to start with
    int shortestJourneyTime = 50000000;
    Minibus* quickestBus = NULL;

    // loop through minibuses to find the best one for our user
    for (int i = 0; i <= pf->noBuses; i ++)
    {
        // Calculate the time for this minibus to get to that person
        Minibus* minibus = &minibuses[i];

        if (minibus->occupancy < 1)
        {
            int journeyTime = makeDis(pf->map, pf->edgeCount, minibus->currentStop, request->startStop);

            // If it's not the shortest, ignore it
            if (journeyTime <= shortestJourneyTime)
            {
                quickestBus = minibus;
            }
        }
    }

    // If the quickest time for the bus to get there, plus the travel time to destination is too late, we say so...
    int travelTime = makeDis(pf->map, pf->edgeCount, request->startStop, request->destinationStop);
    // If it's gonna take too long to get there, or there's no buses available, we can't accommodate request
    if (!quickestBus || (shortestJourneyTime + currentTime) >= (request->desiredBoardingTime + pf->maxDelay))
    {
        printf("request cannot be accommodated\n");
    }
    else
    {
        printf("-> minibus %d is on its way! Gunna be there in %d mins ok c u then xx\n", quickestBus->id, travelTime);
        //delay(5000);

        // We need to make a new event at the future time, with a callback function
        int executionTime = travelTime + currentTime;
        request->minibus = quickestBus;
        Event *event = createEvent(executionTime, busArrived, request);
        addToEventQueue(*event);
    }

    //Request_destroy(request);
}

Simulation *Simulation_create(ParsedFile *pf) {
    // Allocate enough memory to create a new and check we have enough memory
    Simulation *simulation = malloc(sizeof(Simulation));
    assert(simulation != NULL);

    simulation->pf = pf;

    return simulation;
}

void Simulation_start(Simulation *simulation)
{
    ParsedFile *pf = simulation->pf;

    // There's a fixed amount of minibuses in the system, let's make these first and store in array
    Minibus * minibuses = createMinibuses(pf);

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
        //if (currentTime % requestRate == 0)
        //{
            // Make a new (random) request
            Passenger* passenger = Passenger_create();
            Request* request = Passenger_make_request(simulation);
            passenger->request = request;
            Request_print(request);

            // Now we need to do something with this request...
            // This will calculate the SHORTEST time (in minutes) for a bus to get here...
            findBus(pf, minibuses, passenger, currentTime);
            //Passenger_destroy(passenger);
        //}

        // At this time t, are there any events?
        // If yes, we need to execute their callback function
        EventQueue *eq = findInEventQueue(currentTime, NULL);
        if (eq)
        {
            Event event = eq->event;
            event.callbackFunction(event.data);
        }

        printf("current time %d\n", currentTime);
        simulation->currentTime++;
    }

    // Free up the memory

}

Minibus * createMinibuses(ParsedFile *pf)
{
    // Create an array of pointers to the minibuses that we've created
    Minibus *minibuses = malloc(pf->noBuses * sizeof(Minibus*));
    for (int total = 0; total < pf->noBuses; total++)
    {
        minibuses[total] = *Minibus_create(total, 0, 0, pf->busCapacity);
    }
    return minibuses;
}

