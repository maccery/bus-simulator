#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

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
    printf("hey");
    // We need to get the input file, which is our first argument
    char *fileName = argv[1];
    printf("%s", fileName);

    FILE* file = fopen(fileName, "r");
    char line[5];

    if (file == NULL)
    {
        die("No file found");
    }

    printf("hey");

    /* assume line is a char array */
    while (fgets(line, sizeof line, file) != NULL) {
        printf("hey");
    }

    fclose(file);

    return 0;
}
