//
// Created by Tom Macmichael on 19/11/2015.
//

#include "parser.h"
#include <assert.h>
#include "dijkstra.h"
#include "simulation.h"

ParsedFile *ParsedFile_create(int busCapacity, int boardingTime, float requestRate, float pickupInterval,
                                     int maxDelay, int noBuses, int noStops, int stopTime) {
    // Allocate enough memory to create a new struct and check we have enough memory
    ParsedFile *file = malloc(sizeof(ParsedFile));
    assert(file != NULL);

    file->busCapacity = busCapacity;
    file->boardingTime = boardingTime;
    file->requestRate = requestRate;
    file->pickupInterval = pickupInterval;
    file->maxDelay = maxDelay;
    file->noStops = noStops;
    file->stopTime = stopTime;

    return file;
}

void ParsedFile_destroy(ParsedFile *file) {
    assert(file != NULL);
    free(file);
}

void ParsedFile_print(ParsedFile *file) {
    printf("Bus capacity: %d", file->busCapacity);
    printf("\nBoarding time: %d", file->boardingTime);
    printf("\nRequest rate: %f", file->requestRate);
    printf("\nPickup interval: %f", file->pickupInterval);
    printf("\nMax delay: %d", file->maxDelay);
    printf("\nNo buses: %d", file->noBuses);
    printf("\nNo stops: %d", file->noStops);
    printf("\nStop time: %d", file->stopTime);
    printf("\n");
}

void ParsedFile_mapPrint(ParsedFile *file)
{
    int i,j;

    for (i = 0; i < MATRIX_HEIGHT; i++) {
        for (j = 0; j < MATRIX_WIDTH; j++) {
            printf("%d ", file->map[i][j]);
        }
        printf("\n");
    }
}

void die(const char *message) {
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

void printParsedFile(ParsedFile *parsedFile)
{
    ParsedFile_print(parsedFile);
    ParsedFile_mapPrint(parsedFile);
    ParsedFile_destroy(parsedFile);
}

/**
 * Parses a given file
 * @return ParsedFile
 */
Simulation *parseFile(FILE *file)
{
    int noBuses[5];
    char line[256];

    if (file == NULL) {
        die("No file found");
    }

    char *variableName;
    char *value;

    // create an empty struct to store the parsed data
    ParsedFile *parsedFile = ParsedFile_create(0, 0, 0.0, 0.0, 0, 0, 0, 0);

    // Now let's loop through the contents of the file, line by line
    int lineNumber = -1;
    while (fgets(line, sizeof line, file) != NULL) {
        variableName = strtok(line, " ");  // e.g busCapacity
        value = strtok(NULL, " ");         // e.g the value of busCapacity, i.e 12


        if (variableName != NULL) {
            if (strcmp(variableName, "busCapacity") == 0) {
                parsedFile->busCapacity = atoi(value);
                if (parsedFile->busCapacity > 24)
                {
                    die("The bus capacity can't be greater than 24 seats");
                }
            }
            else if (strcmp(variableName, "boardingTime") == 0) {
                parsedFile->boardingTime = atoi(value);
            }
            else if (strcmp(variableName, "requestRate") == 0) {
                parsedFile->requestRate = atoi(value);
            }
            else if (strcmp(variableName, "pickupInterval") == 0) {
                parsedFile->pickupInterval = atoi(value) * 60; // time is given in minutes
            }
            else if (strcmp(variableName, "maxDelay") == 0) {
                parsedFile->maxDelay = atoi(value) * 60; // time is given in minutes
            }
            else if (strcmp(variableName, "noBuses") == 0) {
                // If the value is experiment, we know the next few numbers are gonna be experiment values (up to 5)
                if (strcmp(value,"experiment") == 0)
                {
                    // Loop through the next tokens until we're at the end of the line
                    int i = 0;
                    for (char *p = strtok(NULL," "); p != NULL; p = strtok(NULL, " ")) {
                        noBuses[i] = atoi(p);
                        i++;
                    }
                }
                else
                {
                    noBuses[0] = atoi(value);
                }
            }
            else if (strcmp(variableName, "noStops") == 0) {
                parsedFile->noStops = atoi(value);
                if (parsedFile->noStops > MATRIX_HEIGHT)
                {
                    die("The number of bus stops can't be greater than the MATRIX_HEIGHT");
                }
            }
            else if (strcmp(variableName, "stopTime") == 0) {
                parsedFile->stopTime = atoi(value) * 60 * 60; // time is given in hours
            }
            else if (lineNumber > -1 || strcmp(variableName, "map\n") == 0) {

                // Essentially says to skip this if we're just on the 'map' definition line
                if (lineNumber > -1) {

                        // We've already got the first two values, so we'll store them
                        parsedFile->map[lineNumber][0] = atoi(variableName);
                        parsedFile->map[lineNumber][1] = atoi(value);


                    if (atoi(variableName) != -1)
                    {
                        parsedFile->edgeCount++;
                    }

                    if (atoi(value) != -1)
                    {
                        parsedFile->edgeCount++;
                    }

                        int charNumber = 2; //  also same as the edgenumber
                    for (char *p = strtok(NULL," "); p != NULL; p = strtok(NULL, " "))
                    {
                        parsedFile->map[lineNumber][charNumber] = atoi(p);
                        if (atoi(p) != -1)
                        {
                            parsedFile->edgeCount++;
                        }
                        charNumber++;
                    }

                    if (charNumber != parsedFile->noStops)
                    {
                        die("The matrix map doesn't match the number of stops");
                    }
                }
                lineNumber++;
            }
        }
    }
    if (lineNumber != parsedFile->noStops)
    {
        die("The matrix map doesn't match the number of stops");
    }
    fclose(file);

    // Create an array of pointers to the simulators that we've created
    int numberOfSimulations = 5;
    Simulation *simulations = malloc(numberOfSimulations * sizeof(Simulation*));

    // Make simulators for every combination of noBuses
    for (int i = 0; i < 5; i++)
    {
        if (noBuses[i])
        {
            // Make a copy of the parsed file, but update it with our no buses parameters
            ParsedFile *parsedFileCopy = malloc(sizeof(ParsedFile));
            *parsedFileCopy = *parsedFile;
            parsedFileCopy->noBuses = noBuses[i];
            simulations[i] = *Simulation_create(parsedFileCopy);
        }
    }

    return simulations;
}
