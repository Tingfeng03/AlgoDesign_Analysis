#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define START_SIZE 1000
#define END_SIZE 10000000
#define STEP_FACTOR 10

void generate_random_data(int64_t size) {
    char filename[50];
    sprintf(filename, "dataset_%d.txt", size); //format filename

    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Unable to open file");
        return;
    }

    for (int64_t i=0; i<size; i++) {
        // multiply size-1 to ensure a wider range of number
        int64_t random_num = (rand() * (size - 1) / RAND_MAX) + 1;
        fprintf(file, "%lld\n", random_num);
    }

    fclose(file);
}

int main() {
    // Seed the random number generator
    srand(time(0));

    for (int64_t i = START_SIZE; i < END_SIZE; i *= STEP_FACTOR) {
        for(int64_t size = i; size < i *10; size += i) {
            generate_random_data(size);
        }       
    }
    generate_random_data(END_SIZE);

    return 0;
}