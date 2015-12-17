//
// Created by Tom Macmichael on 17/12/2015.
//

#ifndef CSLP_FLLOYD_H
#define CSLP_FLLOYD_H

#define INF INT_MAX
#include <limits.h>


int floydWarshell(int graph[][6], int source, int destination);
int makeDis(int map[12][12] , int edgeCount, int source, int destination);

#endif //CSLP_FLLOYD_H
