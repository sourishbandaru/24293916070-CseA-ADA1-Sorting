#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Insertion Sort
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main() {
    srand(time(NULL));
    FILE *fp;

    // Predefined array of sizes
    int sizes[10] = {0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 10000};

    fp = fopen("insertion_data.txt", "w"); // overwrite each run
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    int trials = 5; // average across multiple runs for accuracy

    for (int k = 0; k < 10; k++) {
        int n = sizes[k];
        if (n == 0) {
            fprintf(fp, "0 0.0\n");
            printf("0 0.0\n");
            continue;
        }

        double total_time = 0.0;

        for (int t = 0; t < trials; t++) {
            int *arr = (int*)malloc(n * sizeof(int));
            if (arr == NULL) {
                printf("Memory allocation failed for size %d!\n", n);
                continue;
            }

            // Generate random numbers
            for (int i = 0; i < n; i++) {
                arr[i] = rand() % 100000;
            }

            clock_t start, end;
            start = clock();
            insertionSort(arr, n);
            end = clock();

            total_time += ((double)(end - start)) / CLOCKS_PER_SEC;

            free(arr);
        }

        double avg_time = total_time / trials;

        // Print result
        printf("%d %.6f\n", n, avg_time);

        // Save to file
        fprintf(fp, "%d %.6f\n", n, avg_time);
    }

    fclose(fp);
    return 0;
}
