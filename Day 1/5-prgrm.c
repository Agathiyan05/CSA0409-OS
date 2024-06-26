#include <stdio.h>
struct Process {
    int processID;
    int priority;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
};
void sortProcessesByPriority(struct Process processes[], int n) {

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].priority > processes[j + 1].priority) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}
void calculateWaitingTime(struct Process processes[], int n) {
    processes[0].waitingTime = 0; 

    for (int i = 1; i < n; i++) {
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
    }
}
void calculateTurnaroundTime(struct Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
    }
}
void calculateAverageTimes(struct Process processes[], int n) {
    double totalWaitingTime = 0, totalTurnaroundTime = 0;

    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    double averageWaitingTime = totalWaitingTime / n;
    double averageTurnaroundTime = totalTurnaroundTime / n;

    printf("Average Waiting Time: %.2f\n", averageWaitingTime);
    printf("Average Turnaround Time: %.2f\n", averageTurnaroundTime);
}

void displayGanttChart(struct Process processes[], int n) {
    printf("\nGantt Chart:\n");
    printf("------------------------------------------------------\n");
    printf("| Process ID | Priority | Burst Time | Waiting Time |\n");
    printf("------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("| %11d | %8d | %10d | %13d |\n",
               processes[i].processID, processes[i].priority,
               processes[i].burstTime, processes[i].waitingTime);
    }

    printf("------------------------------------------------------\n");
}
int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];

    printf("Enter the priority and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].processID = i + 1;
        printf("Process %d: ", i + 1);
        scanf("%d %d", &processes[i].priority, &processes[i].burstTime);
    }
    sortProcessesByPriority(processes, n);
    calculateWaitingTime(processes, n);
    calculateTurnaroundTime(processes, n);
    displayGanttChart(processes, n);
    calculateAverageTimes(processes, n);

    return 0;
}