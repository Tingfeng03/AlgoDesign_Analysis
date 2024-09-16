#ifndef PROJECT1_FILE_H
#define PROJECT1_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


long int* read_data_from_file(const char *filename, long int size) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open file");
        return NULL;
    }

    // optional, but help allocate the correct amount of memory 
    long int count = 0;
    long int temp;
    while (fscanf(file, "%li", &temp) != EOF) {
        count++;
    }

    if (size != count) return NULL;
    // Allocate memory for storing integers
    long int *data = (long int *)malloc(count * sizeof(long int));
    if (!data) {
        perror("Memory allocation fail");
        fclose(file);
        size = 0;
        return NULL;
    }

    // reset file pointer to the beginning of the file
    rewind(file);

    // read integers into the array
    long int i=0; 
    while (fscanf(file, "%li", &data[i]) != EOF) {
        i++;
    }

    fclose(file);

    return data;
}

#endif //PROJECT1_FILE_H
