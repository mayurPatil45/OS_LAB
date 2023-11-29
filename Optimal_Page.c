#include <stdio.h>
#include <limits.h>

// Function to find the index of the page that will not be used for the longest time in the future
int findOptimal(int referenceString[], int pagesInFrame[], int start, int n) {
    int index = -1, farthest = start;
    for (int i = 0; i < n; i++) {
        int j;
        for (j = start; j < n; j++) {
            if (pagesInFrame[i] == referenceString[j]) {
                if (j > farthest) {
                    farthest = j;
                    index = i;
                }
                break;
            }
        }

        // If the page is not found in the future, return its index
        if (j == n) {
            return i;
        }
    }
    return (index == -1) ? 0 : index;
}

// Function to simulate Optimal page replacement algorithm
int optimalPageReplacement(int referenceString[], int n, int frameSize) {
    int frame[frameSize];
    int pageFaults = 0;

    // Initialize frame array with -1 indicating an empty slot
    for (int i = 0; i < frameSize; i++) {
        frame[i] = -1;
    }

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

            // Find the page to replace using the Optimal algorithm
            int replaceIndex = findOptimal(referenceString, frame, i + 1, n);

            // Replace the page
            frame[replaceIndex] = currentPage;
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
    int pageFaults = optimalPageReplacement(referenceString, n, frameSize);
    printf("\nNumber of Page Faults: %d\n", pageFaults);

    return 0;
}
