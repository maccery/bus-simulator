#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

struct ParsedFile {
    int busCapacity;
    int boardingTime;
    float requestRate;
    float pickupInterval;
    int maxDelay;
    int noBuses;
    int noStops;
};


struct ParsedFile *ParsedFile_create(int busCapacity, int boardingTime, float requestRate, float pickupInterval, int maxDelay, int noBuses, int noStops)
{
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

    return file;
}

void ParsedFile_destroy(struct ParsedFile *file)
{
    assert(file != NULL);

    free(file);
}

void ParsedFile_print(struct ParsedFile *file)
{
    printf("Bus capacity: %d", file->busCapacity);
    printf("\nBoarding time: %d", file->boardingTime);
    printf("\nRequest rate: %f", file->requestRate);
    printf("\nPickup interval: %f", file->pickupInterval);
    printf("\nMax delay: %d", file->maxDelay);
    printf("\nNo buses: %d", file->noBuses);
    printf("\nNo stops: %d", file->noStops);
}

void die(const char *message)
{
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

int main(int argc, char *argv[])
{
    // We need to get the input file, which is our first argument
    char *fileName = argv[1];
    FILE* file = fopen(fileName, "r");
    char line[256];

    if (file == NULL)
    {
        die("No file found");
    }

    char *variableName;
    char *value;
    char *text;

    // create an empty struct to store the parsed data
    struct ParsedFile *parsedFile = ParsedFile_create(0,0,0.0,0.0,0,0,0);

    // Now let's loop through the contents of the file, line by line
    while (fgets(line, sizeof line, file) != NULL) {
        variableName = strtok(line, " ");  // e.g busCapacity
        value = strtok(NULL, " ");         // e.g the value of busCapacity, i.e 12

        if (variableName != NULL) {
            if (strcmp(variableName, "busCapacity") == 0)
            {
                parsedFile->busCapacity = atoi(value);
            }
            if (strcmp(variableName, "boardingTime") == 0)
            {
                parsedFile->boardingTime = atoi(value);
            }
            if (strcmp(variableName, "requestRate") == 0)
            {
                parsedFile->requestRate = atoi(value);
            }
            if (strcmp(variableName, "pickupInterval") == 0)
            {
                parsedFile->pickupInterval = atoi(value);
            }
            if (strcmp(variableName, "maxDelay") == 0)
            {
                parsedFile->maxDelay = atoi(value);
            }
            if (strcmp(variableName, "noBuses") == 0)
            {
                parsedFile->noBuses = atoi(value);
            }
            if (strcmp(variableName, "noStops") == 0)
            {
                parsedFile->noStops = atoi(value);
            }
        }
    }
    fclose(file);

    ParsedFile_print(parsedFile);
    ParsedFile_destroy(parsedFile);

    return 0;
}
