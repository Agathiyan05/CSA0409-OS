#include<stdio.h>

struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};
void nonPreemptiveSJF(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    int total_time = 0;

    printf("\nGantt Chart:\n");

    for (int i = 0; i < n; i++) {
        processes[i].completion_time = total_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

        for (int t = total_time; t < processes[i].completion_time; t++) {
            printf("P%d ", processes[i].process_id);
        }

        total_time = processes[i].completion_time;
    }
    printf("\n\n");
}
int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Enter arrival time and burst time for process P%d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
    }
    nonPreemptiveSJF(processes, n);
    printf("\nProcess\t Turnaround Time\t Waiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t %d\t\t\t %d\n", processes[i].process_id, processes[i].turnaround_time, processes[i].waiting_time);
    }
    return 0;
}