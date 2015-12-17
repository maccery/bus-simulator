//
// Created by Tom Macmichael on 17/12/2015.
//

#include "flloyd.h"
int floydWarshell(int graph[6][6], int source, int destination){
    int V = 6;
    int dist[250][250], i, j, k;

    for(i=0; i<V; i++){
        for(j=0; j<V; j++){
            dist[i][j] = graph[i][j];
        }
    }

    for(k=0; k<V; k++){
        for(i=0;i<V;i++){
            for(j=0;j<V;j++){
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    if (dist[source][destination] == INF)
        return 0;
    else
        return dist[source][destination];
}


int makeDis(int map[12][12] , int edgeCount, int source, int destination)
{

    int graph[6][6];
    for (int rows = 0; rows <= 6; rows++)
    {
        for (int columns = 0; columns <= 6; columns++)
        {
            if (map[rows][columns] != -1)
            {
                graph[rows][columns] = map[rows][columns];
            }
            else
            {
                graph[rows][columns] = INF;
            }
        }
    }
    return floydWarshell(graph, source, destination);
}
