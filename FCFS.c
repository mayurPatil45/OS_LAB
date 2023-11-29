#include <stdio.h>

// Function to calculate finish time, turnaround time, and waiting time
void calculateTimes(int processes[], int n, int bt[]) {
    int wt[n], tat[n], ft[n];

    // Calculate waiting time for each process
    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    // Calculate turnaround time and finish time for each process
    for (int i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
        ft[i] = wt[i] + bt[i];
    }

    // Display the results
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\tFinish Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], bt[i], wt[i], tat[i], ft[i]);
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
    int n;

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

    // Calculate and display finish time, turnaround time, and waiting time
    calculateTimes(processes, n, burstTime);

    return 0;
}
