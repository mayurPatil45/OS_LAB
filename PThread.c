#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ROWS 3
#define COLS 3
#define NUM_THREADS 2

int matrixA[ROWS][COLS];
int matrixB[ROWS][COLS];
int resultMatrix[ROWS][COLS];

// Structure to pass parameters to the thread function
struct ThreadData {
    int threadId;
};

// Function to perform matrix addition in a specific row range
void* matrixAddition(void* args) {
    struct ThreadData* data = (struct ThreadData*)args;
    int startRow = (data->threadId * ROWS) / NUM_THREADS;
    int endRow = ((data->threadId + 1) * ROWS) / NUM_THREADS;

    for (int i = startRow; i < endRow; i++) {
        for (int j = 0; j < COLS; j++) {
            resultMatrix[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }

    pthread_exit(NULL);
}

int main() {
    // Initialize matrices
    printf("Matrix A:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            matrixA[i][j] = rand() % 10;
            printf("%d ", matrixA[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix B:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            matrixB[i][j] = rand() % 10;
            printf("%d ", matrixB[i][j]);
        }
        printf("\n");
    }

    // Initialize Pthreads
    pthread_t threads[NUM_THREADS];
    struct ThreadData threadData[NUM_THREADS];

    // Create threads for matrix addition
    for (int i = 0; i < NUM_THREADS; i++) {
        threadData[i].threadId = i;
        pthread_create(&threads[i], NULL, matrixAddition, (void*)&threadData[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Display the result matrix
    printf("\nResult Matrix (Matrix A + Matrix B):\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", resultMatrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
