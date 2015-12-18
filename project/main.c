#include <stdio.h>
#include <unistd.h>
#include "parser.h"
#include "simulation.h"

int errors;

// TESTS 0
void testAverageDuration ()
{
    Statistics *testStats = Statistics_create(45,5,0,0,0);
    int average = averageDuration(testStats);
    assert(average == 9);
}
// TEST 1
void testAverageDurationWithZero ()
{
    Statistics *testStats = Statistics_create(0,0,0,0,0);
    int average = averageDuration(testStats);
    assert(average == 0);
}

void runTests()
{
    testAverageDuration();
    //testAverageDurationWithZero();
    printf("\n--------All tests passed, yay-------\n");
}

int main(int argc, char *argv[]) {

    runTests();

    // We need to get the input file, which is our first argument
    char *fileName = argv[1];
    FILE *file = fopen(fileName, "r");

    ParsedFile *pf = parseFile(file);

    ParsedFile_print(pf);
    sleep(1);

    Simulation *simulation = Simulation_create(pf);
    Statistics* statistics = Simulation_start(simulation);

    printStatistics(statistics);

    //ParsedFile_destroy(pf);

}