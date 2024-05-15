/*******************************************************************************
* Filename : edf.c
* Author : Yash Yagnik
* Date : 3/7/2024
* Description : Earliest Deadline First Scheduling Algorithm
* Pledge : I pledge my honor that I have abided by the Stevens Honor System.
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

// Structure to represent a process
typedef struct Process {
    int id;               // Process ID
    int cpu_time;         // CPU time required by the process
    int period;           // Period of the process
    int deadline;         // Current deadline of the process
    int remaining_cpu;    // Remaining CPU time for the current period
    struct Process *next; // Pointer to the next process in the linked list
} Process;

// Function to calculate the Greatest Common Divisor (GCD) using Euclid's algorithm
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

// Function to calculate the Least Common Multiple (LCM) of two numbers
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

// Function to insert a process into a linked list in sorted order based on deadlines
void insertProcess(Process **head, Process *newProcess) {
    Process *current = *head;
    Process *prev = NULL;

    while (current != NULL && current->deadline <= newProcess->deadline) {
        prev = current;
        current = current->next;
    }

    if (prev == NULL) {
        newProcess->next = *head;
        *head = newProcess;
    } 
    else {
        newProcess->next = current;
        prev->next = newProcess;
    }
}

int main() {
    int num_processes;

    // Step 1: Enter the number of processes
    printf("Enter the number of processes to schedule: ");
    scanf("%d", &num_processes);

    // Step 2: Enter process details
    Process *processes = NULL;
    for (int i = 0; i < num_processes; i++) {
        Process *newProcess = malloc(sizeof(Process));

        printf("Enter the CPU time of process %d: ", i + 1);
        scanf("%d", &newProcess->cpu_time);

        printf("Enter the period of process %d: ", i + 1);
        scanf("%d", &newProcess->period);

        newProcess->id = i + 1;
        newProcess->deadline = newProcess->period;
        newProcess->remaining_cpu = newProcess->cpu_time;
        newProcess->next = NULL;

        insertProcess(&processes, newProcess);
    }

    // Calculate MaxTime (Least Common Multiple of all periods)
    int max_time = processes->period;
    Process *current = processes->next;
    while (current != NULL) {
        max_time = lcm(max_time, current->period);
        current = current->next;
    }

    // Allocate an array to store the execution schedule
    int *schedule = malloc(max_time * sizeof(int));

    // Initialize the schedule array with -1 (indicating idle time)
    for (int i = 0; i < max_time; ++i) {
        schedule[i] = -1;
    }

    // Step 3: Schedule processes using Earliest Deadline First algorithm
    int total_waiting_time = 0;
    int total_processes_created = 0;
    int pros_start = 0;
    for (int time = 0; time < max_time; time++) {
        // Enqueue processes with deadlines up to the current time
        current = processes;
        
        while (current != NULL && current->deadline <= max_time && current->remaining_cpu > 0) {
            // Print the current list of processes
            
            Process *temp = processes;
            while (temp != NULL&& !pros_start) {
                printf("%d: processes (oldest first):", time);
                printf(" %d (%d ms)", temp->id, temp->remaining_cpu);
                printf("\n");
                temp = temp->next;
                //pros_start = 1;
            }
            

            // Start the process
            if (schedule[time] == -1 && !pros_start) {
                schedule[time] = current->id;
                printf("%d: process %d starts\n", time, current->id);
                pros_start = 1;
            }

            // Decrement remaining CPU time
            current->remaining_cpu--;

            // Check if the process completed its execution
            if (current->remaining_cpu == 0) {
                printf("%d: process %d ends\n", time + 1, current->id);
                pros_start = 0;
                // Calculate waiting time
                int waiting_time = time + 1 - current->deadline;
                if (waiting_time < 0) {
                    waiting_time = 0;  // Ensure waiting time is non-negative
                }
                total_waiting_time += waiting_time;

                // Update process details for the next period
                current->deadline += current->period;
                current->remaining_cpu = current->cpu_time;

                

                // Increment total processes created
                total_processes_created++;

                // Dequeue the completed process
                processes = processes->next;
                free(current);
            }

            current = current->next;
        }
    }

    // Step 4: Print the summary
    printf("%d: Max Time reached\n", max_time);
    printf("Sum of all waiting times: %d\n", total_waiting_time);
    printf("Number of processes created: %d\n", total_processes_created);

    // Calculate and print the Average Waiting Time
    double average_waiting_time = (double)total_waiting_time / total_processes_created;
    printf("Average Waiting Time: %.2lf\n", average_waiting_time);

    // Free allocated memory
    free(schedule);

    // Free remaining linked list nodes
    current = processes;
    while (current != NULL) {
        Process *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
