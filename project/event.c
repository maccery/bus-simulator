//
// Created by Tom Macmichael on 16/12/2015.
//

#include "event.h"
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

Event* searchEventQueue(Simulation *simulation) {
    EventQueue *tmp = head;
    //printf("Events in the event queue currently: ");
    while (tmp != NULL) {
        if (tmp->event.executionTime == simulation->currentTime) {
            return &tmp->event;
        }

        //printf("%d, ", tmp->event.executionTime);
        tmp = tmp->next;
    }
    //printf("\n");
    return NULL;
}

EventQueue* addToEventQueue(Event event, Simulation *simulation)
{
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

    if (event.executionTime == simulation->currentTime)
    {
        event.executionTime++;
    }

    ptr->event = event;
    ptr->next = NULL;

    ptr->next = head;
    head = ptr;

    return ptr;
}