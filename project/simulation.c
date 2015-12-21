//
// Created by Tom Macmichael on 24/11/2015.
//

#include <stdbool.h>
#include <unistd.h>
#include "simulation.h"
#include "dijkstra.h"
#include "event.h"

Simulation *simulation;
Statistics *statistics;

int busArrivedAtDestination(void *data) {
    Request *request = (Request*) data;

    Passenger_disembark(request, request->minibus);

    // We can now destroy the passenger and the request
    Request_destroy(request);

    return 1;
}

/*
 * Disembarks any passengers from minibus' current stop
 */
void disembarkAllPassengers(Minibus *minibus) {

    printf("checking disembark status. Minibus is at %d \n", minibus->currentStop);
    Request *blankRequest = Request_create(-1,-1,-1);
    Request * r = stopsForMinibus(minibus, simulation, blankRequest);
    for (int i = 0; i <= 12; i++)
    {
        Request *request = &r[i];
        if (request->destinationStop == -1) break;
        printf ("request destination %d\n", request->destinationStop);

        if (request->destinationStop == minibus->currentStop)
        {
            Passenger_disembark(request, request->minibus);
        }
        printf("line %d", i);
    }
}

// Boarding pasenger callback
int boardedPassenger(void *data) {
    Request *request = (Request*) data;
    Passenger_embark(request, request->minibus);

    // We now need to remove this event from the queue and pick up more folk
    int travelTime = makeDis(simulation->pf->map, simulation->pf->edgeCount, request->startStop, request->destinationStop);
    int destinationTime = travelTime + simulation->currentTime;

    Event *event = createEvent(destinationTime, busArrived, request);
    addToEventQueue(*event, simulation);

    // Update statistics
    statistics->totalTrips = statistics->totalTrips + 1;
    statistics->tripTotalLength = statistics->tripTotalLength + travelTime;

    return 5;
}

// Handles the situation when bus arrived
int busArrived(void *data) {
    Request *request = (Request*) data;

    // Let's mark us arrived
    request->minibus->currentStop = request->startStop;

    // It takes some time to board the passengers, make event for this
    int executionTime = simulation->currentTime + simulation->pf->boardingTime;

    // If we've arrived early, we can't depart yet
    if (request->desiredBoardingTime > executionTime)
    {
        executionTime = request->desiredBoardingTime + simulation->pf->boardingTime;
    }
    // If we didn't arrive earlier, we need to record our waiting time
    else
    {
        int waitingTime = executionTime - request->desiredBoardingTime;
        statistics->totalWaitingTime = statistics->totalWaitingTime + waitingTime;
    }


    printf("-> minibus %d arrived at stop %d. Waiting to depart at %d\n", request->minibus->id, request->startStop, request->desiredBoardingTime);
    disembarkAllPassengers(request->minibus);


    // Queue the event for when we board the passenger (i.e in ~10 seconds)
    Event *event = createEvent(executionTime, boardedPassenger, request);
    addToEventQueue(*event, simulation);
    return 5;
}

// Global eventqueue
EventQueue *eventQueue = NULL;


int route(int startStop, int endStop, int time, int boardingTime)
{
    int shortestPath =  makeDis(simulation->pf->map, simulation->pf->edgeCount, startStop, startStop);
    int endTime = time + shortestPath;
    if (endTime <= (boardingTime + simulation->pf->maxDelay))
    {
        return endTime;
    }
    else
    {
        return -1;
    }
}


void makeEvents(Event * e)
{
    int arraySize = 10;
    for (int i = 0; i <= arraySize; i++)
    {
        if (e[i].executionTime >= simulation->currentTime)
        {
            //printf("Making an eventlol\n");
            addToEventQueue(e[i], simulation);
        }
    }
}

// Removes all future events for a minibus
void removeEvents(Minibus *minibus)
{
    removeFromEventQueue(minibus);
}


int recurse(Request * r, Minibus *startingMinibus, int makeEvent)
{
    int fail = 0;
    int arraySize = 10;
    Event *events = malloc(12 * sizeof(Event*));

    for (int i = 0; i <= arraySize; i++)
    {
        int time = simulation->currentTime;
        time = route(startingMinibus->currentStop, r[i].startStop, time, r[i].desiredBoardingTime);

        Request *previous = &r[i];

        if (previous->startStop == previous->destinationStop) break;

        //printf("i: %i, Going from minibus current location %d -> %d; time is gonna be %d\n", i, startingMinibus->currentStop, r[i].startStop, time);

        for (int j = 0; j <= arraySize; j++)
        {
            if (r[j].startStop == r[j].destinationStop) break;

            time = route(previous->startStop, r[j].startStop, time, r[j].desiredBoardingTime);
            //printf("j: %d, Going from %d -> %d; time is gonna be %d\n", j, previous->startStop, r[j].startStop, time);
            previous = &r[j];

            if (time == -1)
            {
                fail = 1;
            }
            r[j].minibus = startingMinibus;
            events[j] = *createEvent(time, busArrived, &r[j]);

        }
        if (fail == 0)
        {
            if (makeEvent == 1)
            {
                removeEvents(startingMinibus);
                makeEvents(events);
            }
            return 1;
        }
    }

    return 0;
}

/* Can minibus take in new request */
int isReroutingPossible(Minibus *minibus, Request *request, int makeEvents)
{

    //printf("is re-routing possible for minibus %d?\n", minibus->id);
    // Get all the stops that this minibus is current scheduled to stop at
    // with our new request appended
    Request * r = stopsForMinibus(minibus, simulation, request);

    int reRoutingPossible = recurse(r, minibus, makeEvents);
    if (reRoutingPossible == 1)
    {
       // printf("Yes. It's indeed possible for minibus %d to take in this request.\n", minibus->id);
        return 1;
    }
    //printf("\n");
    return -1;
}


/*
 * Possible events:
 * - new passenger request
 * - arrival at a bus stop
 * - disembarkation of a passenger
 * - boarding of a new passenger
 */
void findBus(Simulation *simulation, Minibus * minibuses, Request* request)
{
    ParsedFile *pf = simulation->pf;

    // Really large shortest journey time to start with
    int shortestJourneyTime = 50000000;
    Minibus* quickestBus = NULL;

    formatTime(simulation->currentTime);

    //printf("FIND BUS FOR THIS REQUEST, loop through buses\n");
    // loop through minibuses to find the best one for our user
    Minibus *chosenBus;
    for (int i = 0; i <= pf->noBuses; i ++)
    {
        // Calculate the time for this minibus to get to that person
        Minibus* minibus = &minibuses[i];

        if (minibus->occupancy < pf->busCapacity) {

            // Can we possible route any buses here?
            if (isReroutingPossible(minibus, request, 0) == 1)
            {
             //   printf("WE'VE CHOSEN A BUS...IT'S %d\n", minibus->id);
                 chosenBus = minibus;
            }
        }

        //stopsForMinibus(request->minibus, simulation);
//        printEventQueues();
    }
   // printf("Loop over\n");
    if (chosenBus)
    {
        isReroutingPossible(chosenBus, request, 1);
    }
    else
    {
        printf("We can't do that request, sorry.\n");
    }

    statistics->totalRequests++;

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

void makeRandomRequest()
{

    ParsedFile *pf = simulation->pf;
    float timeUntilNextRequest = exponentialRand((float) (60*pf->requestRate));
    int executionTime = (int) timeUntilNextRequest + simulation->currentTime;

    makeRequest(executionTime);
}

int makeRequestCallback(void *data) {

    makeRandomRequest();

    // Make a new (random) request
    Request* request = Request_random(simulation);
    Request_print(request);

    // Now we need to do something with this request...
    // This will calculate the SHORTEST time (in minutes) for a bus to get here...
    findBus(simulation, simulation->minibuses, request);
}

void makeRequest(int executionTime)
{
    Event *event = createEvent(executionTime, makeRequestCallback, NULL);
    addToEventQueue(*event, simulation);
}


Statistics* Simulation_start(Simulation *simulation)
{
    statistics = Statistics_create(0,0,0,0,0);

    ParsedFile *pf = simulation->pf;

    // There's a fixed amount of minibuses in the system, let's make these first and store in array
    Minibus * minibuses = createMinibuses(pf);
    simulation->minibuses = minibuses;

    // Start with one request
    makeRandomRequest();

    // Our simulation algorithm, boom
    for (int currentTime = 0; currentTime <= pf->stopTime; currentTime++)
    {
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

