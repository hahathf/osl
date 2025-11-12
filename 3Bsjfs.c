#include <stdio.h>

struct Process 
{ 
    int id; 
    int arrivalTime; 
    int burstTime; 
    int waitingTime; 
    int turnAroundTime; 
}; 

void calculateTimes(struct Process proc[], int n) 
{ 
    int totalWaitingTime = 0, totalTurnAroundTime = 0; 
    int completionTime[n]; 

    // Sorting processes based on arrival time, then burst time
    for (int i = 0; i < n - 1; i++) 
    { 
        for (int j = i + 1; j < n; j++) 
        { 
            if (proc[i].arrivalTime > proc[j].arrivalTime || 
                (proc[i].arrivalTime == proc[j].arrivalTime && proc[i].burstTime > proc[j].burstTime)) 
            { 
                struct Process temp = proc[i]; 
                proc[i] = proc[j]; 
                proc[j] = temp; 
            } 
        } 
    } 

    // First process
    completionTime[0] = proc[0].arrivalTime + proc[0].burstTime; 
    proc[0].turnAroundTime = proc[0].burstTime; 
    proc[0].waitingTime = 0; 

    // Remaining processes
    for (int i = 1; i < n; i++) 
    { 
        if (completionTime[i - 1] < proc[i].arrivalTime)
            completionTime[i] = proc[i].arrivalTime + proc[i].burstTime; 
        else
            completionTime[i] = completionTime[i - 1] + proc[i].burstTime; 

        proc[i].turnAroundTime = completionTime[i] - proc[i].arrivalTime; 
        proc[i].waitingTime = proc[i].turnAroundTime - proc[i].burstTime; 
    } 

    // Display results
    printf("\nProcess\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n"); 
    for (int i = 0; i < n; i++) 
    { 
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               proc[i].id, proc[i].burstTime, proc[i].arrivalTime, 
               proc[i].waitingTime, proc[i].turnAroundTime); 

        totalWaitingTime += proc[i].waitingTime; 
        totalTurnAroundTime += proc[i].turnAroundTime; 
    } 

    printf("\nAverage Waiting Time: %.2f\n", (float)totalWaitingTime / n); 
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnAroundTime / n); 
} 

int main() 
{ 
    int n; 
    printf("Enter number of processes: "); 
    scanf("%d", &n); 

    struct Process proc[n]; 

    for (int i = 0; i < n; i++) 
    { 
        proc[i].id = i + 1; 
        printf("Enter arrival time for process %d: ", proc[i].id); 
        scanf("%d", &proc[i].arrivalTime); 
        printf("Enter burst time for process %d: ", proc[i].id); 
        scanf("%d", &proc[i].burstTime); 
    } 

    calculateTimes(proc, n); 
    return 0; 
}
