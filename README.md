# 1 How it was built
Mac OS X El Capitan, using Intellj CLion. Unfortunately CLion only supports CMake files, rather than Make files. However, when compiling the make files using cmake, then using the following commands, it runs fine on my Mac. Unfortunately, it does not on DiCE.

## 1.1 Code structure
I wanted to make the code as object-orientated as possible. Of course C is not an object-orientated language, however using Structs I could almost replicate the behaviour.
All my different “objects” were split into individual files, with their own struct definition. Example below for Minibus.

    typedef struct Minibus {
       int id;
       int currentStop;
       int occupancy; // Current occupancy of the bus
       int capacity; // Maximum number of people the bus can have
    } Minibus;


This allowed me to create Minibus “objects” and update their values in a way that is human-readable and is consistent with other languages.

    minibus->occupancy = minibus->occupancy-1;
    minibus->currentStop = request->destinationStop;

All my code was modularised, so that it could be tested. I tried to split the code into as many small functions as possible.

# 2 The basics
## 2.1 Parsing
My parser.c file takes a File and parses it. The ordering of the lines doesn’t matter and it works well. It checks that the matrix map size corresponds with the noStops provided. It also checks that the bus capacity does not exceed 24 seats, as per our requirement.

## 2.2 Simulation
Once parsed, the parsed details are passed onto the simulation.c file, which generates random requests (using the input mean rate, as per the specification).

## 2.3 Events system
The requests are then put onto an EventsQueue (see event.c), to execute at a given time. Whenever time is incremented, we check the events queue to see whether or not there are any events to be executed. If so, we call their callback function and execute it.

## 2.4 Bus system
In my bus system, there is a re-routing algorithm. It loops through the minibuses and checks the upcoming events for that minibus. It works out which stops it needs to visit, and by when, and then decides whether that minibus can accept the new incoming request, while still agreeing with the criteria for all its current requests.
If it can accept it, it removes all upcoming events for that bus and re-creates new events (with updated pickup times) based on the fact we’re now taking in a new request.
At any stop, it disembarks any passengers with that as their destination.
 The algorithm itself works fine, albeit inefficiently. However there is a memory issue that causes it to break at the moment.

## 2.5 Experiments
I did implement an experiments system, with the taxi system. However there were limitations: if you wanted to change the number of experiments you would have to do this in the code, due to the fact the array size is fixed. You can see this on the /feature/experiments git branch.

# 3 Statistics
Not all the statistics are running, however the statistics structure is in place and is easily updated. We simply update the statistics object as such:

    statistics->totalTrips = statistics->totalTrips + 1;
    statistics->tripTotalLength = statistics->tripTotalLength + travelTime;

# 4 Shortest path algorithm
I used[Bellman-Ford’s algorithm](http://www.geeksforgeeks.org/dynamic-programming-set-23-bellman-ford-algorithm/)for this. However, I modified the code so that it
would integrate with my parser. Below is the code for calculating the distance between a
source and destination.

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

Here, I am looping through the given map and creating a new “edge” from each source and destination. If it’s a -1, then we don’t create an edge. This was not the most efficient way to do it, but it worked well.

# 5 Tests
I played about with multiple testing frameworks such as Google Test and mi- nunit. However I had trouble running my Google Tests as these have to be written in C++, whereas my code is C. Minunit was a simple testing framework that I did start with but did not have time to write tests for my entire code.
