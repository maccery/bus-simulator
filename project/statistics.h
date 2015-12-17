//
// Created by Tom Macmichael on 17/12/2015.
//

#include <stdio.h>

typedef struct Statistics {
    int totalTrips;
    int tripTotalLength;
    int totalWaitingTime;
    int totalMissed;
    int totalRequests;
} Statistics;

Statistics *Statistics_create();

int averageDuration(Statistics *statistics);
float averageOccupancy(Statistics *statistics);
int averageWaitingTime(Statistics *statistics);

void formatTimeToMins(int seconds);
void printStatistics(Statistics *statistics);