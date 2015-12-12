#include <stdio.h>
#include "parser.h"
#include "simulation.h"
#include "dijkstra.h"

int main(int argc, char *argv[]) {
    // We need to get the input file, which is our first argument
    char *fileName = argv[1];
    FILE *file = fopen(fileName, "r");

    struct ParsedFile *pf = parseFile(file);

    //ParsedFile_print(pf);
    //Simulation_start(pf);
    //ParsedFile_destroy(pf);

    makeDis(pf->graph, 4);
}