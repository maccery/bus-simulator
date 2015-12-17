//
// Created by Tom Macmichael on 17/12/2015.
//

#include <assert.h>
#include <stdlib.h>
#include "statistics.h"

Statistics *Statistics_create() {
    Statistics *statistics = malloc(sizeof(Statistics));
    assert(statistics != NULL);

    statistics->tripTotalLength = 0;
    statistics->totalTrips = 0;

    return statistics;
}

int tripDuration(Statistics *statistics) {
    int totalTrips = statistics->totalTrips;
    int tripTotalLength = statistics->tripTotalLength;

    return tripTotalLength/totalTrips;
}

void formatTimeToMins(int seconds)
{
    int hours = seconds / 3600;
    int remainder = seconds % 3600;
    int minutes = remainder / 60;
    int secs = remainder % 60;

    printf("%d:%d", minutes, secs);
}

void printStatistics(Statistics *statistics)
{
    int averageDuration = tripDuration(statistics);

    printf("average trip duration <average duration (");
    formatTimeToMins(averageDuration);
    printf(")");
}