//
// Created by Tom Macmichael on 17/12/2015.
//

#include <stdio.h>

typedef struct Statistics {
    int totalTrips;
    int tripTotalLength;
    int tripEfficiency;
    float missedRequests;
    int averageWaitTime;
    int averageTripDeviation;
} Statistics;

Statistics *Statistics_create();

int tripDuration(Statistics *statistics);
void formatTimeToMins(int seconds);
void printStatistics(Statistics *statistics);