//
// Created by Filip Niedzielski on 14/09/2023.
//


#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/pstat.h"

int main(int argc, char *argv[]) {
    struct pstat ps;

    // Call the user-side function to invoke the system call.
    if (getpinfo(&ps) < 0) {
        printf("Error getting process info.\n");
        exit(1);
    }

    // Print the processes info from the filled `pstat` struct.
    printf("PID\tTickets\tTicks\tIn Use\n");
    printf("----------------------------\n");
    for (int i = 0; i < NPROC; i++) {
        if (ps.inuse[i]) {
            printf("%d\t%d\t%d\t%d\n", ps.pid[i], ps.tickets[i], ps.ticks[i], ps.inuse[i]);
        }
    }

    exit(0);
}



