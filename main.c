#include <stdio.h>
#include "parser.h"
#include "request.h"

int main(int argc, char *argv[]) {
    // We need to get the input file, which is our first argument
    char *fileName = argv[1];
    FILE *file = fopen(fileName, "r");

    struct ParsedFile *pf = parseFile(file);

    ParsedFile_print(pf);

    // Our simulation algorithm, boom
    for (int currentTime = 0; currentTime <= pf->stopTime; currentTime++)
    {
        // Generate a random request and print it
        struct Request* request = Request_random(currentTime, pf->noStops);
        Request_print(request);
        Request_destroy(request);
    }
}