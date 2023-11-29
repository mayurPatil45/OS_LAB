#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
int sharedData = 0;
int readersCount = 0;

void *reader(void *arg) {
    pthread_mutex_lock(&mutex);
    readersCount++;

    // First reader locks the resource for writing
    if (readersCount == 1) {
        printf("First reader locks the resource for writing.\n");
        // Simulate reading
        sleep(1);
    }

    pthread_mutex_unlock(&mutex);

    // Reading
    printf("Reader reads: %d\n", sharedData);

    pthread_mutex_lock(&mutex);
    readersCount--;

    // Last reader unlocks the resource for writing
    if (readersCount == 0) {
        printf("Last reader unlocks the resource for writing.\n");
        // Simulate more reading
        sleep(1);
    }

    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

void *writer(void *arg) {
    pthread_mutex_lock(&mutex);

    // Writing
    sharedData++;
    printf("Writer writes: %d\n", sharedData);

    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    pthread_t readerThread1, readerThread2, writerThread1, writerThread2;

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    // Create reader and writer threads
    pthread_create(&readerThread1, NULL, reader, NULL);
    pthread_create(&readerThread2, NULL, reader, NULL);
    pthread_create(&writerThread1, NULL, writer, NULL);
    pthread_create(&writerThread2, NULL, writer, NULL);

    // Wait for threads to finish
    pthread_join(readerThread1, NULL);
    pthread_join(readerThread2, NULL);
    pthread_join(writerThread1, NULL);
    pthread_join(writerThread2, NULL);

    // Clean up
    pthread_mutex_destroy(&mutex);

    return 0;
}
