//
// Created by Tom Macmichael on 16/12/2015.
//

#ifndef CSLP_EVENT_H
#define CSLP_EVENT_H

#include <stdbool.h>
#include "simulation.h"

typedef struct Event {
    int executionTime; // the time at which this event occurs
    int (*callbackFunction)(void*); // this is the callback function
    void *data;
} Event;

Event *createEvent(int executionTime, int (*callbackFunction)(void*), void *data);

typedef struct EventQueue
{
    Event event;
    struct EventQueue *next;
} EventQueue;

EventQueue* addToEventQueue(Event event, Simulation *simulation);
EventQueue* betterSearch(int executionTime, Simulation *simulation);
int deleteFromEventQueue(Event event);
extern void formatTime(int seconds);
void executeEvents(int executionTime);


#endif //CSLP_EVENT_H
