#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <math.h> // For rounding

#include "read_datasets.h" // Include the header file
#include "sort.h"

#define START_SIZE 1000
#define END_SIZE 10000000
#define STEP_FACTOR 10
#define NUM_SETS 5

// Function prototypes for writing results to a file
void diff_n();
void diff_s();
void diff_n_s();
void mergesort_performance();
void insertionsort_performance();
void combined_sort_performance();
int check_sorted(long int* data, long int size) {
    for (int i=1; i<size; i++) {
        if (data[i] < data[i-1]) return 0;
    }
    return 1;
}

int main()
{
    diff_n();
    //diff_s();
    //diff_n_s();
    //mergesort_performance();
    // insertionsort_performance();
    // combined_sort_performance();

    return 0;
}

void diff_n()
{
    // different n
    const char *output_file = "fixed_S.csv"; // Output file to write average number of key comparisons
    FILE *file = fopen(output_file, "w");
    if (!file)
    {
        perror("Unable to open output file");
        return;
    }
    fprintf(file, "n,S,Average Key Comparisons,Average Time (s)\n");
    int S = 32;
    uint64_t keyComp;
    double total_time;
    double avg_time;
    uint64_t avg_keyComp;

    clock_t start, end;

    for (uint64_t i = START_SIZE; i <= END_SIZE; i *= STEP_FACTOR)
    {
        for (uint64_t size = i; size < i * 10; size += i)
        {
            if (size > END_SIZE)
                break;

            char filename[50];
            sprintf(filename, "dataset/dataset_%li_%d.txt", size, 1); // Example filename, will not be used

            total_time = 0.0;
            avg_keyComp = 0;

            for (int set_number = 1; set_number <= NUM_SETS; set_number++)
            {
                keyComp = 0;                
                sprintf(filename, "dataset/dataset_%li_%d.txt", size, set_number); // format filename

                long int *data = read_data_from_file(filename, size); // Read data from the input file
                if (!data)
                {
                    printf("Failed to read data from the file.\n");
                    return;
                }

                start = clock();
                hybrid_sort(data, 0, size - 1, S, &keyComp);
                end = clock();
                if(check_sorted(data, size) == 0) {
                    printf("Not sorted\n");
                } 
                double time = ((double)(end - start)) / CLOCKS_PER_SEC;

                total_time += time;
                avg_keyComp += keyComp;

                free(data);
            }

            avg_time = total_time / NUM_SETS;
            avg_keyComp = (uint64_t)round((double)avg_keyComp / NUM_SETS);

            // Write the results to the output file
            fprintf(file, "%li,%d,%llu,%0.6f\n", size, S, avg_keyComp, avg_time);
            printf("%s \n", filename); // verifying purpose
        }
    }
    fclose(file);
}

void diff_s()
{
    // different S
    const char *output_file = "fixed_n_100k.csv"; // Output file to write average number of key comparisons
    FILE *file = fopen(output_file, "w");
    if (!file)
    {
        perror("Unable to open output file");
        return;
    }
    fprintf(file, "n,S,Average Key Comparisons,Average Time (s)\n");

    uint64_t keyComp;
    double total_time;
    double avg_time;
    uint64_t avg_keyComp;

    clock_t start, end;
    long int size = 100000; // n = 100k 

    for (int S = 1; S <= 100; S += 1)
    {
        //int S = 200;
        total_time = 0.0;
        avg_keyComp = 0;

        char filename[50];
        sprintf(filename, "dataset/dataset_%li.txt", size); // fix n = 1000000

        for (int set_number = 1; set_number <= NUM_SETS; set_number++)
        {
            keyComp = 0;
            sprintf(filename, "dataset/dataset_%li_%d.txt", size, set_number); // format filename

            long int *data = read_data_from_file(filename, size); // Read data from the input file
            if (!data)
            {
                printf("Failed to read data from the file.\n");
                return;
            }

            start = clock();
            hybrid_sort(data, 0, size - 1, S, &keyComp);
            end = clock();
            double time = ((double)(end - start)) / CLOCKS_PER_SEC;

            total_time += time;
            avg_keyComp += keyComp;

            free(data);
        }

        // Calculate average time and value of key comparison 
        avg_time = total_time / NUM_SETS;
        avg_keyComp = (uint64_t)round((double)avg_keyComp / NUM_SETS);

        // Write the results to the output file
        fprintf(file, "%li,%d,%llu,%0.6f\n", size, S, avg_keyComp, avg_time);
        printf("%i \n", S); // verifying purpose
    }
    fclose(file);
}

void diff_n_s()
{
    const char *output_file = "diff_n_s.csv"; // Output file to write number of key comparisons
    FILE *file = fopen(output_file, "w");
    if (!file)
    {
        perror("Unable to open output file");
        return;
    }
    fprintf(file, "n,S,Key Comparisons,time\n");

    uint64_t avg_Comp;
    double avg_time;

    clock_t start, end;

    for (int i = START_SIZE; i <= END_SIZE; i *= STEP_FACTOR)
    {
            
        char filename[50];


        for (int S = 1; S <= 100; S += 1)
        {
            uint64_t totalcomp = 0;
            double totaltime = 0;
            
            for (int index = 1; index <= NUM_SETS; index++)
            {
                sprintf(filename, "dataset/dataset_%llu_%d.txt", i, index); // format filename

                long int *data = read_data_from_file(filename, i); // Read data from the input file
                if (!data)
                {
                    printf("Failed to read data from the file.\n");
                    return;
                }
                

                // int *temp = (int *)malloc(i * sizeof(int));
                // if (!temp)
                // {
                //     printf("Memory allocation failed.\n");
                //     return;
                // }
                //for (int j = 0; j < i; j++)
                //    temp[j] = data[j];

                start = clock();
                hybrid_sort(data, 0, i - 1, S, &totalcomp);
                end = clock();
                totaltime += ((double)(end - start)) / CLOCKS_PER_SEC;
                //free(temp);
                free(data);
            }

            avg_time = totaltime / NUM_SETS;
            avg_Comp = (uint64_t)round((double)totalcomp / NUM_SETS);

            // Write the results to the output file
            fprintf(file, "%llu,%d,%llu,%0.6f\n", i, S, avg_Comp, avg_time);
            printf("%s, %i\n", filename, S); // veryfying purpose
        }
        
    }
    fclose(file);
}

void mergesort_performance() {
    const char *output_file = "mergesort_10m.csv"; // Output file to write average number of key comparisons
    FILE *file = fopen(output_file, "w");
    if (!file)
    {
        perror("Unable to open output file");
        return;
    }
    fprintf(file, "n,Average Key Comparisons,Average Time (s)\n");
    uint64_t keyComp;
    double total_time;
    double avg_time;
    uint64_t avg_keyComp;

    clock_t start, end;

    int size = 10000000; // set the size of n to 100000

    char filename[50];
    sprintf(filename, "dataset/dataset_%li_%d.txt", size, 1); // Example filename, will not be used

    total_time = 0.0;
    avg_keyComp = 0;

    for (int set_number = 1; set_number <= NUM_SETS; set_number++)
    {
        keyComp = 0;                
        sprintf(filename, "dataset/dataset_%li_%d.txt", size, set_number); // format filename

        long int *data = read_data_from_file(filename, size); // Read data from the input file
        if (!data)
        {
            printf("Failed to read data from the file.\n");
            return;
        }

        start = clock();
        mergesort(data, 0, size - 1, &keyComp);
        end = clock();
        if(check_sorted(data, size) == 0) {
                printf("Not sorted\n");
            } 
        double time = ((double)(end - start)) / CLOCKS_PER_SEC;

        total_time += time;
        avg_keyComp += keyComp;

        free(data);
    }

    avg_time = total_time / NUM_SETS;
    avg_keyComp = (uint64_t)round((double)avg_keyComp / NUM_SETS);

    // Write the results to the output file
    fprintf(file, "%li,%llu,%0.6f\n", size, avg_keyComp, avg_time);
    printf("%s \n", filename); // verifying purpose
        
    
    fclose(file);
}
// // Similar changes apply to other functions such as mergesort_performance, insertionsort_performance, etc.
