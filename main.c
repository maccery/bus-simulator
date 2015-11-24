#include <stdio.h>
#include "parser.h"
#include "request.h"
#include "minibus.h"
#include "passenger.h"

int main(int argc, char *argv[]) {
    // We need to get the input file, which is our first argument
    char *fileName = argv[1];
    FILE *file = fopen(fileName, "r");

    struct ParsedFile *pf = parseFile(file);

    ParsedFile_print(pf);

    // Our simulation algorithm, boom
    for (int currentTime = 0; currentTime <= pf->stopTime; currentTime++)
    {
        // Convert request rate in seconds
        int requestRate = (int) pf->requestRate*60;

        // We only want to create a request with the request rate....
        if (currentTime % requestRate == 0)
        {
            // Make a new request
            struct Passenger* passenger = Passenger_create();
            struct Request* request = Passenger_make_request(passenger, pf->noStops);
            Request_print(request);
            Request_destroy(request);
        }

        // Create our buses; 0 capacity, and at the bus garage
        struct Minibus* minibus = Minibus_create(0, 0, pf->busCapacity, pf->boardingTime);

        Minibus_destroy(minibus);
    }
}