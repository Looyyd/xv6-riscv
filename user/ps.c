//
// Created by Filip Niedzielski on 14/09/2023.
//


#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/pstat.h"
#include "kernel/proc.h"

#include "pstat.h" // Include the header for the pstat structure
#include "user.h"  // For system call interfaces and printf

int
main(int argc, char *argv[])
{
    struct pstat pstat; // Define the pstat structure

    if(getpinfo(&pstat) != 0) {
        printf("Error retrieving process information\n");
        exit(1);
    }

    printf("PID\tTickets\tTicks\tIn Use\n"); // Header
    printf("----------------------------\n");
    for (int i = 0; i < NPROC; i++) {
        if(pstat.inuse[i]) { // Print only processes that are in use
            printf("%d\t%d\t%d\t%d\n", pstat.pid[i], pstat.tickets[i], pstat.ticks[i], pstat.inuse[i]);
        }
    }

    exit(0);
}


