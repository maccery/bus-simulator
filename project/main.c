#include <stdio.h>
#include <unistd.h>
#include "parser.h"
#include "simulation.h"


void runSimulator(Simulation *simulation) {
    Statistics* statistics = Simulation_start(simulation);
    printStatistics(statistics);
    ParsedFile_print(simulation->pf);
}

int main(int argc, char *argv[]) {
    // We need to get the input file, which is our first argument
    char *fileName = argv[1];
    FILE *file = fopen(fileName, "r");
    Simulation *simulations = parseFile(file);

    // Loop through the simulations, and run them
    for (int i = 0; i < 9; i++)
    {
        printf("\n------------ EXPERIMENT %d ---------------\n",i);
        if (&simulations[i])
        {
            runSimulator(&simulations[i]);
            sleep(1);
        }
        printf("\n");
    }


    //ParsedFile_destroy(pf);

}