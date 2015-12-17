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

    // We need to loop through all the noBuses experiments
    for (int i = 0; i < 5; i++)
    {
        if (pf->noBuses[i])
        {
            printf("EXPERIMENT %d\n", i+1);
            Simulation *simulation = Simulation_create(pf);
            Statistics* statistics = Simulation_start(simulation);
            printStatistics(statistics);
        }
    }

    //ParsedFile_destroy(pf);

}