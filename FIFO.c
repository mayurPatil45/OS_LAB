#include <stdio.h>

// Function to find the index of the oldest page in the frame
int findOldest(int frame[], int frameSize) {
    int oldestIndex = 0;
    for (int i = 1; i < frameSize; i++) {
        if (frame[i] < frame[oldestIndex]) {
            oldestIndex = i;
        }
    }
    return oldestIndex;
}

// Function to simulate FIFO page replacement algorithm
int fifoPageReplacement(int referenceString[], int n, int frameSize) {
    int frame[frameSize];
    int pageFaults = 0;

    // Initialize frame array with -1 indicating an empty slot
    for (int i = 0; i < frameSize; i++) {
        frame[i] = -1;
    }

    int frameIndex = 0; // Index to keep track of the current position in the frame array

    for (int i = 0; i < n; i++) {
        int currentPage = referenceString[i];
        int pageFound = 0;

        // Check if the page is already in the frame
        for (int j = 0; j < frameSize; j++) {
            if (frame[j] == currentPage) {
                pageFound = 1;
                break;
            }
        }

        if (!pageFound) {
            // Page fault occurred
            pageFaults++;
            frame[frameIndex] = currentPage; // Replace the oldest page in the frame
            frameIndex = (frameIndex + 1) % frameSize; // Move to the next position in the frame
        }

        // Display the current state of the frame
        printf("Frame: ");
        for (int j = 0; j < frameSize; j++) {
            if (frame[j] == -1) {
                printf("[ ] ");
            } else {
                printf("[%d] ", frame[j]);
            }
        }
        printf("\n");
    }

    return pageFaults;
}

int main() {
    int n, frameSize;

    // Input the number of pages in the reference string
    printf("Enter the number of pages in the reference string: ");
    scanf("%d", &n);

    int referenceString[n];

    // Input the reference string
    printf("Enter the reference string:\n");
    for (int i = 0; i < n; i++) {
        printf("Page %d: ", i + 1);
        scanf("%d", &referenceString[i]);
    }

    // Input the size of the page frame
    printf("Enter the size of the page frame: ");
    scanf("%d", &frameSize);

    // Calculate and display the number of page faults
    int pageFaults = fifoPageReplacement(referenceString, n, frameSize);
    printf("\nNumber of Page Faults: %d\n", pageFaults);

    return 0;
}
