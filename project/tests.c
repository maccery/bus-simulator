//
// Created by Tom Macmichael on 18/12/2015.
//

#include <assert.h>
#include "tests.h"
#include "statistics.h"
#include "simulation.h"

// --------- TESTS
// TEST 0
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

// TEST MAKE REQUEST
void testMakeRequest()
{
    // Make a request
    makeRequest(0);
    // Test it exists

}

void runTests()
{

    {
        testAverageDuration();
        testAverageDurationWithZero();
        printf("\n--------All tests passed, yay-------\n");
    }
}