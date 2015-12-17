// A C / C++ program for Bellman-Ford's single source
// shortest path algorithm.

#include "dijkstra.h"

// Creates a graph with V vertices and E edges
struct Graph* createGraph(int V, int E)
{
    struct Graph* graph =
            (struct Graph*) malloc( sizeof(struct Graph) );
    graph->V = V;
    graph->E = E;

    graph->edge =
            (struct Edge*) malloc( graph->E * sizeof( struct Edge ) );

    return graph;
}

// A utility function used to print the solution
void printArr(int dist[], int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

// The main function that finds shortest distances from src to
// all other vertices using Bellman-Ford algorithm.  The function
// also detects negative weight cycle
int BellmanFord(struct Graph* graph, int src, int destination)
{
    int V = graph->V;
    int E = graph->E;
    int dist[V];

    // Step 1: Initialize distances from src to all other vertices
    // as INFINITE
    for (int i = 0; i < V; i++)
        dist[i]   = INT_MAX;
    dist[src] = 0;

    // Step 2: Relax all edges |V| - 1 times. A simple shortest
    // path from src to any other vertex can have at-most |V| - 1
    // edges
    for (int i = 1; i <= V-1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }

    // Step 3: check for negative-weight cycles.  The above step
    // guarantees shortest distances if graph doesn't contain
    // negative weight cycle.  If we get a shorter path, then there
    // is a cycle.
    for (int i = 0; i < E; i++)
    {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
            printf("Graph contains negative weight cycle");
    }

    return dist[destination];
}

/**
 * Given a start and destination, will calculate the shortest time between these...
 */
int makeDis(int map[12][12] , int edgeCount, int source, int destination)
{
    struct Graph* g = createGraph(6, edgeCount);
    int counter = 0;
    for (int rows = 0; rows <= 6; rows++)
    {
        for (int columns = 0; columns <= 6; columns++)
        {
            if (map[rows][columns] != -1)
            {

                g->edge[counter].src = rows;
                g->edge[counter].dest = columns;
                g->edge[counter].weight = map[rows][columns];

                counter++;
            }
        }
    }
    int timeInMinutes = BellmanFord(g, source, destination);
    return timeInMinutes*60;
}