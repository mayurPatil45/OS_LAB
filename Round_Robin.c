#include <stdio.h>

#define MAX 10

// Function to calculate finish time, turnaround time, and waiting time using Round Robin algorithm
void calculateTimes(int processes[], int n, int bt[], int quantum) {
    int wt[n], tat[n], remainingTime[n];

    // Copy burst times to remainingTime array
    for (int i = 0; i < n; i++) {
        remainingTime[i] = bt[i];
    }

    int t = 0; // Current time
    int flag; // Flag to check if any process is remaining

    do {
        flag = 0;

        for (int i = 0; i < n; i++) {
            if (remainingTime[i] > 0) {
                flag = 1;

                // Process for the time quantum or remaining burst time, whichever is smaller
                if (remainingTime[i] > quantum) {
                    t += quantum;
                    remainingTime[i] -= quantum;
                } else {
                    t += remainingTime[i];
                    wt[i] = t - bt[i];
                    remainingTime[i] = 0;
                }
            }
        }
    } while (flag);

    // Calculate turnaround time
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }

    // Display the results
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\tFinish Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], bt[i], wt[i], tat[i], tat[i] + wt[i]);
    }

    // Calculate average turnaround time and waiting time
    float avgTAT = 0, avgWT = 0;
    for (int i = 0; i < n; i++) {
        avgTAT += tat[i];
        avgWT += wt[i];
    }
    avgTAT /= n;
    avgWT /= n;

    printf("\nAverage Waiting Time: %.2f", avgWT);
    printf("\nAverage Turnaround Time: %.2f\n", avgTAT);
}

int main() {
    int n, quantum;

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n];
    int burstTime[n];

    // Input burst time for each process
    printf("Enter the burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &burstTime[i]);
        processes[i] = i + 1; // Process IDs start from 1
    }

    // Input time quantum
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    // Calculate and display finish time, turnaround time, and waiting time
    calculateTimes(processes, n, burstTime, quantum);

    return 0;
}
