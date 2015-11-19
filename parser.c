//
// Created by Tom Macmichael on 19/11/2015.
//

#include "parser.h"
#include <assert.h>


struct ParsedFile *ParsedFile_create(int busCapacity, int boardingTime, float requestRate, float pickupInterval,
                                     int maxDelay, int noBuses, int noStops, int stopTime) {
    // Allocate enough memory to create a new struct and check we have enough memory
    struct ParsedFile *file = malloc(sizeof(struct ParsedFile));
    assert(file != NULL);

    file->busCapacity = busCapacity;
    file->boardingTime = boardingTime;
    file->requestRate = requestRate;
    file->pickupInterval = pickupInterval;
    file->maxDelay = maxDelay;
    file->noBuses = noBuses;
    file->noStops = noStops;
    file->stopTime = stopTime;

    return file;
}

void ParsedFile_destroy(struct ParsedFile *file) {
    assert(file != NULL);
    free(file);
}

void ParsedFile_print(struct ParsedFile *file) {
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

void ParsedFile_mapPrint(struct ParsedFile *file) {
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

void printParsedFile(struct ParsedFile *parsedFile)
{
    ParsedFile_print(parsedFile);
    ParsedFile_mapPrint(parsedFile);
    ParsedFile_destroy(parsedFile);
}

void parseFile(FILE *file)
{
    char line[256];

    if (file == NULL) {
        die("No file found");
    }

    char *variableName;
    char *value;

    // create an empty struct to store the parsed data
    struct ParsedFile *parsedFile = ParsedFile_create(0, 0, 0.0, 0.0, 0, 0, 0, 0);

    // Now let's loop through the contents of the file, line by line
    int lineNumber = -1;
    while (fgets(line, sizeof line, file) != NULL) {
        variableName = strtok(line, " ");  // e.g busCapacity
        value = strtok(NULL, " ");         // e.g the value of busCapacity, i.e 12


        if (variableName != NULL) {
            if (strcmp(variableName, "busCapacity") == 0) {
                parsedFile->busCapacity = atoi(value);
            }
            else if (strcmp(variableName, "boardingTime") == 0) {
                parsedFile->boardingTime = atoi(value);
            }
            else if (strcmp(variableName, "requestRate") == 0) {
                parsedFile->requestRate = atoi(value);
            }
            else if (strcmp(variableName, "pickupInterval") == 0) {
                parsedFile->pickupInterval = atoi(value);
            }
            else if (strcmp(variableName, "maxDelay") == 0) {
                parsedFile->maxDelay = atoi(value);
            }
            else if (strcmp(variableName, "noBuses") == 0) {
                parsedFile->noBuses = atoi(value);
            }
            else if (strcmp(variableName, "noStops") == 0) {
                parsedFile->noStops = atoi(value);
            }
            else if (strcmp(variableName, "stopTime") == 0) {
                parsedFile->stopTime = atoi(value);
            }
            else if (lineNumber > -1 || strcmp(variableName, "map\n") == 0) {

                // Essentially says to skip this if we're just on the 'map' definition line
                if (lineNumber > -1) {
                    // We've already got the first two values, so we'll store them
                    parsedFile->map[lineNumber][0] = atoi(variableName);
                    parsedFile->map[lineNumber][1] = atoi(value);

                    int charNumber = 2;
                    for (char *p = strtok(NULL," "); p != NULL; p = strtok(NULL, " "))
                    {
                        parsedFile->map[lineNumber][charNumber] = atoi(p);
                        charNumber++;
                    }
                }
                lineNumber++;
            }
        }
    }
    fclose(file);

    printParsedFile(parsedFile);
}
