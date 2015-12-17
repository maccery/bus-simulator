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

int averageDuration(Statistics *statistics) {
    return statistics->tripTotalLength / statistics->totalTrips;
}

int averageOccupancy(Statistics *statistics) {
    return 1;
}

int averageWaitingTime(Statistics *statistics) {
    return statistics->totalWaitingTime / statistics->totalTrips;
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
    printf("\n---average trip duration <average duration (");
    formatTimeToMins(averageDuration(statistics));
    printf(")>\n");

    printf("trip efficiency <average occupancy per time unit (%d)>\n", averageOccupancy(statistics));

    printf("average waiting time <%d> seconds---\n", averageWaitingTime(statistics));

}