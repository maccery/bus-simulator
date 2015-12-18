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
    for (int total = 0; total < 5; total++) {
        printf("SIMULATION %d\n", total);
        Simulation *simulation = &simulations[total];
        runSimulator(simulation);
    }

    sleep(1);

    //ParsedFile_destroy(pf);

}