//
// Created by Filip Niedzielski on 23/09/2023.
//

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/pstat.h"

int main(int argc, char *argv[]) {
    int *ptr = 0; // Null pointer
    printf("Dereferencing Null: %d\n", *ptr); // Dereference null pointer
  exit(0);
}