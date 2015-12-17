//
// Created by Tom Macmichael on 24/11/2015.
//

#include <stdbool.h>
#include <unistd.h>
#include "simulation.h"
#include "flloyd.h"
#include "event.h"
#include "passenger.h"

Simulation *simulation;
Statistics *statistics;

int busArrivedAtDestination(void *data) {
    Request *request = (Request*) data;

    Passenger_disembark(request, request->minibus);

    return 1;
}

// Boarding pasenger callback
int boardedPassenger(void *data) {
    Request *request = (Request*) data;
    Passenger_embark(request, request->minibus);

    // We now need to remove this event from the queue and pick up more folk
    int travelTime = makeDis(simulation->pf->map, simulation->pf->edgeCount, request->startStop, request->destinationStop);
    int destinationTime = travelTime + simulation->currentTime;
    formatTime(simulation->currentTime);

    Event *event = createEvent(destinationTime, busArrivedAtDestination, request);
    addToEventQueue(*event, simulation);

    // Update statistics
    statistics->totalTrips = statistics->totalTrips + 1;
    statistics->tripTotalLength = statistics->tripTotalLength + travelTime;

    return 5;
}

// Handles the situation when bus arrived
int busArrived(void *data) {

    Request *request = (Request*) data;
    printf("-> minibus %d arrived at stop %d. Waiting to depart at %d\n", request->minibus->id, request->startStop, request->desiredBoardingTime);

    // It takes some time to board the passengers, make event for this
    int executionTime = simulation->currentTime + simulation->pf->boardingTime;

    // If we've arrived early, we can't depart yet
    if (request->desiredBoardingTime > executionTime)
    {
        executionTime = request->desiredBoardingTime + simulation->pf->boardingTime;
    }

    Event *event = createEvent(executionTime, boardedPassenger, request);
    addToEventQueue(*event, simulation);

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
void findBus(Simulation *simulation, Minibus * minibuses, Passenger* passenger)
{
    Request *request = passenger->request;
    ParsedFile *pf = simulation->pf;

    // Really large shortest journey time to start with
    int shortestJourneyTime = 50000000;
    Minibus* quickestBus = NULL;

    formatTime(simulation->currentTime);

    // loop through minibuses to find the best one for our user
    for (int i = 0; i < pf->noBuses; i ++)
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
                shortestJourneyTime = journeyTime;
            }
        }
    }

    int executionTime = shortestJourneyTime + simulation->currentTime;

    // If it's gonna take too long to get there, or there's no buses available, we can't accommodate request
    if (!quickestBus)
    {
        printf("Request cannot be accommodated. All minibuses are at maximum capacity\n");
    }
    else if(executionTime >= (request->desiredBoardingTime + pf->maxDelay))
    {
        printf("Request cannot be accommodated. No bus will get there in desired time.\n");
    }
    else
    {
        printf("-> minibus %d is scheduled to arrive there at ", quickestBus->id);
        formatTime(executionTime);
        printf("\n");

        // We need to make a new event at the future time, with a callback function
        quickestBus->occupancy++;
        request->minibus = quickestBus;
        // we wanna mark this bus as busy
        Minibus_print(request->minibus);
        Event *event = createEvent(executionTime, busArrived, request);
        addToEventQueue(*event, simulation);
//        printEventQueues();
    }

    //Request_destroy(request);
}

Simulation *Simulation_create(ParsedFile *pf) {
    // Allocate enough memory to create a new and check we have enough memory
    Simulation *s = malloc(sizeof(Simulation));
    assert(s != NULL);

    s->pf = pf;

    simulation = s;

    return s;
}

Statistics* Simulation_start(Simulation *simulation)
{
    statistics = Statistics_create();

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
        int requestRate = (int) pf->requestRate;

        // We only want to create a request with the request rate...
        if (currentTime % requestRate == 0)
        {
            // Make a new (random) request
            Passenger* passenger = Passenger_create();
            Request* request = Passenger_make_request(simulation);
            passenger->request = request;
            formatTime(simulation->currentTime);
            Request_print(request);

            // Now we need to do something with this request...
            // This will calculate the SHORTEST time (in minutes) for a bus to get here...
            findBus(simulation, minibuses, passenger);
            //Passenger_destroy(passenger);
        }

        // At this time t, are there any events?
        // If yes, we need to execute their callback function
        executeEvents(simulation->currentTime);
        simulation->currentTime = currentTime;
    }

    // Free up the memory
    return statistics;
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

