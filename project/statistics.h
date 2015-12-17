//
// Created by Tom Macmichael on 17/12/2015.
//

#include <stdio.h>

typedef struct Statistics {
    int totalTrips;
    int tripTotalLength;
    int totalWaitingTime;
} Statistics;

Statistics *Statistics_create();

int averageDuration(Statistics *statistics);
int averageOccupancy(Statistics *statistics);
int averageWaitingTime(Statistics *statistics);

void formatTimeToMins(int seconds);
void printStatistics(Statistics *statistics);