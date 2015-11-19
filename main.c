#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct ParsedFile {
    int busCapacity;
    int boardingTime;
    float requestRate;
    float pickupInterval;
    int maxDelay;
    int noBuses;
    int noStops;
};

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

    // Now let's loop through the contents of the file, line by line
    while (fgets(line, sizeof line, file) != NULL) {
        variableName = strtok(line, " ");  // e.g busCapacity
        value = strtok(NULL, " ");         // e.g the value of busCapacity, i.e 12
        printf("Variable: %s, Value: %s\n", variableName, value);
    }

    fclose(file);

    return 0;
}
