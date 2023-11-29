#include <stdio.h>

// Function to find the index of the least recently used page in the frame
int findLRU(int recent[], int frameSize) {
    int lruIndex = 0;
    for (int i = 1; i < frameSize; i++) {
        if (recent[i] < recent[lruIndex]) {
            lruIndex = i;
        }
    }
    return lruIndex;
}

// Function to simulate LRU page replacement algorithm
int lruPageReplacement(int referenceString[], int n, int frameSize) {
    int frame[frameSize];
    int recent[frameSize]; // Array to keep track of the most recently used index for each page in the frame
    int pageFaults = 0;

    // Initialize frame array with -1 indicating an empty slot
    for (int i = 0; i < frameSize; i++) {
        frame[i] = -1;
        recent[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int currentPage = referenceString[i];
        int pageFound = 0;

        // Check if the page is already in the frame
        for (int j = 0; j < frameSize; j++) {
            if (frame[j] == currentPage) {
                pageFound = 1;
                recent[j] = i + 1; // Update the most recently used index for the page
                break;
            }
        }

        if (!pageFound) {
            // Page fault occurred
            pageFaults++;

            // Find the least recently used page in the frame
            int lruIndex = findLRU(recent, frameSize);

            // Replace the least recently used page with the current page
            frame[lruIndex] = currentPage;
            recent[lruIndex] = i + 1; // Update the most recently used index for the page
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
    int pageFaults = lruPageReplacement(referenceString, n, frameSize);
    printf("\nNumber of Page Faults: %d\n", pageFaults);

    return 0;
}
