#include <stdio.h>
#include "parser.h"
#include "simulation.h"

int doShit() {
    return 5;
}

int main(int argc, char *argv[]) {
    // We need to get the input file, which is our first argument
    char *fileName = argv[1];
    FILE *file = fopen(fileName, "r");

    ParsedFile *pf = parseFile(file);

    ParsedFile_print(pf);
    Simulation_start(pf, doShit);
    //ParsedFile_destroy(pf);

}