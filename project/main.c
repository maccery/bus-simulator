#include <stdio.h>
#include <unistd.h>
#include "parser.h"
#include "simulation.h"


int main(int argc, char *argv[]) {
    // We need to get the input file, which is our first argument
    char *fileName = argv[1];
    FILE *file = fopen(fileName, "r");

    ParsedFile *pf = parseFile(file);

    ParsedFile_print(pf);
    sleep(1);

    Simulation* simulation = Simulation_create(pf);
    Simulation_start(simulation);
    //ParsedFile_destroy(pf);

}