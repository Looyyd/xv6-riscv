//
// Created by Filip Niedzielski on 14/09/2023.
//

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/pstat.h"

volatile int work = 1;

int workload(void) {
    int i, j;
    while (work) {  // Keep looping while the `work` flag is set
        for (i = 0; i < 10; i++)
            for (j = 0; j < 1000; j++);
    }
    return 0;
}

int main(int argc, char *argv[]) {
    int tickets_values[] = {10000, 1, 1, 1, 1, 1};
    int n = sizeof(tickets_values) / sizeof(tickets_values[0]);

    for (int i = 0; i < n; i++) {
        int pid = fork();
        if (pid < 0) {
            printf("Fork failed.\n");
            exit(1);
        }

        if (pid == 0) {  // child
            settickets(tickets_values[i]);
            workload();
            exit(0);
        }
    }

    // Parent gathers and prints statistics every second (or another chosen interval)
    for (int i = 0; i < 2; i++) {  // 10 iterations as an example, can adjust based on needs
        sleep(50);  // Sleep for some time (e.g., 100ms)

        struct pstat ps;
        if (getpinfo(&ps) < 0) {
            printf("Error getting process info.\n");
            exit(1);
        }

        printf("Interval %d:\n", i+1);
        printf("PID\tTickets\tTicks\tIn Use\n");
        printf("----------------------------\n");
        for (int j = 0; j < NPROC; j++) {
            if (ps.inuse[j]) {
                printf("%d\t%d\t%d\t%d\n", ps.pid[j], ps.tickets[j], ps.ticks[j], ps.inuse[j]);
            }
        }
    }

    // Signal child processes to stop working
    work = 0;

    // Parent waits for all children to finish
    for (int i = 0; i < n; i++) {
        wait(0);
    }

    exit(0);
}