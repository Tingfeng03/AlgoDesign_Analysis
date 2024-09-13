#ifndef PROJECT1_SORT_H
#define PROJECT1_SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


void insertion_sort(long int* data, long int n, uint64_t *keyComp) {

    for(long int i = 1; i < n; i++) {
        long int key = data[i];
        long int j = i - 1;

        while (j >= 0 && ++(*keyComp) && data[j] > key) {
            data[j + 1] = data[j]; // swap position
            j -= 1; // move pointer to the front
        }
        data[j + 1] = key; 
    }
}

void merge(long int *data, long int l, long int m, long int r, uint64_t *keyComp) {
    long int i, j, k;
    long int n1 = m - l + 1;
    long int n2 = r - m;

    // create two temp arrays 
    long int *L = (long int *)malloc(n1 * sizeof(long int));
    long int *R = (long int *)malloc(n2 * sizeof(long int));

    // copy data into the temp arrays
    for (i = 0; i < n1; i++) {L[i] = data[l + i];}
    for (j = 0; j < n2; j++) {R[j] = data[m + 1 + j];}

    // merge array L[] and R[] back into data[]
    i = 0; j = 0; k = l;
    
    while (i < n1 && j < n2) {
        (*keyComp)++;
        if (L[i] <= R[j]) {
            data[k] = L[i];
            i++;
        }
        else {
            data[k] = R[j];
            j++;
        }
        k++;
    }

    // merge remaining value if got any
    while (i < n1) {
        data[k] = L[i];
        k++;
        i++;
    }
    while (j < n2) {
        data[k] = R[j];
        k++;
        j++;
    }
    free(L); free(R);
}

void mergesort(long int *data, long int l, long int r, uint64_t *keyComp) {
    if (l >= r) {
        return; 
    }
    long int m = (l + r) / 2;

    mergesort(data, l, m, keyComp);
    mergesort(data, m+1, r, keyComp);
    merge(data, l, m, r, keyComp);

}
void hybrid_sort(long int *data, long int l, long int r, long int S, uint64_t * keyComp) {
    if (r - l  + 1 <= S) {
        insertion_sort(data + l, r-l+1, keyComp);
        return;
    }
    long int m = (l + r) / 2;

    hybrid_sort(data, l, m, S, keyComp);
    hybrid_sort(data, m+1, r, S, keyComp);
    merge(data, l, m, r, keyComp);
    
}

#endif // PROJECT1_SORT_H

/*long int main() {
    // Test array
    long int data[] = {14,40,31,28,3,15,17,51};
    long int n = sizeof(data) / sizeof(data[0]);

    // Print the original array
    printf("Original array:\n");
    for (long int i = 0; i < n; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    // Sort the array using insertion_sort
    long int *keyComparisons = (long int *)malloc(sizeof(long int));
    *keyComparisons = 0;
    hybrid_sort(data, 0, n - 1, 3, keyComparisons);

    // Print the sorted array
    printf("Sorted array:\n");
    for (long int i = 0; i < n; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    // Print the number of key comparisons
    printf("Number of key comparisons: %lld\n", *keyComparisons);

    return 0;
}*/
