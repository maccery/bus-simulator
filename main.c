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
    for (int time = 0; time <= pf->stopTime; time++)
    {
        struct Request* request = Request_random(MATRIX_HEIGHT);
        Request_print(request);
        Request_destroy(request);
    }
}