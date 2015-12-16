//
// Created by Tom Macmichael on 16/12/2015.
//

#include "event.h"


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

EventQueue* addToEventQueue(Event event)
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
    ptr->event = event;
    ptr->next = NULL;

    ptr->next = head;
    head = ptr;

    return ptr;
}

// Finds an event by the exeution time
EventQueue* findInEventQueue(int executionTime, EventQueue **prev)
{
    EventQueue *ptr = head;
    EventQueue *tmp = NULL;
    bool found = false;

    while(ptr != NULL)
    {
        if(ptr->event.executionTime == executionTime)
        {
            found = true;
            break;
        }
        else
        {
            tmp = ptr;
            ptr = ptr->next;
        }
    }

    if(true == found)
    {
        if(prev)
            *prev = tmp;
        return ptr;
    }
    else
    {
        return NULL;
    }
}
