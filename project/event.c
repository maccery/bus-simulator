//
// Created by Tom Macmichael on 16/12/2015.
//

#include "event.h"
#include "request.h"
#include "simulation.h"

void formatTime(int seconds)
{
    int hours = seconds / 3600;
    int remainder = seconds % 3600;
    int minutes = remainder / 60;
    int secs = remainder % 60;

    printf("<%d:%d:%d> <%d> ", hours, minutes, secs, seconds);
}


// creates an event

Event *createEvent(int executionTime, int (*callbackFunction)(void*), void* data)
{
    Event *event = malloc(sizeof(Event));
    event->executionTime = executionTime;
    event->callbackFunction = callbackFunction;
    event->data = data;

    return event;
}

EventQueue *head = NULL;
EventQueue *curr = NULL;

EventQueue* create(Event event)
{
    EventQueue *ptr = (EventQueue*)malloc(sizeof(EventQueue));
    if(NULL == ptr)
    {
        printf("\n Node creation failed \n");
        return NULL;
    }
    ptr->event = event;
    ptr->next = NULL;

    head = curr = ptr;
    return ptr;
}

/*
 * Executes all events at the current time of simulation
 */
void executeEvents(int executionTime) {

    EventQueue *tmp = head;
    while (tmp != NULL) {
        if (tmp->event.executionTime == executionTime) {
            formatTime(executionTime);
            tmp->event.callbackFunction(tmp->event.data);
        }

        tmp = tmp->next;
    }
}

/* Given a minibus, returns all the events for it*/
void stopsForMinibus(Minibus *minibus)
{
    EventQueue *tmp = head;
    while (tmp != NULL) {
        Request *request = (Request*) tmp->event.data;
        if (request) {
        if (request->minibus) {
            if (request->minibus->id == minibus->id) {
                if(tmp->event.callbackFunction == busArrived)
                {
                    printf("Minibus %d has an upcoming stop\n", minibus->id);
                }
            }
        }}

        tmp = tmp->next;
    }
}

EventQueue* addToEventQueue(Event event, Simulation *simulation)
{
    if (event.executionTime == simulation->currentTime)
    {
        event.executionTime = event.executionTime+1;
    }
    printf("added to event queue for execution at %d\n", event.executionTime);
    if(NULL == head)
    {
        return (create(event));
    }

    EventQueue *ptr = (EventQueue*)malloc(sizeof(EventQueue));
    if(NULL == ptr)
    {
        printf("\n Node creation failed \n");
        return NULL;
    }

    ptr->event = event;
    ptr->next = NULL;

    ptr->next = head;
    head = ptr;

    return ptr;
}