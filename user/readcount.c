//
// Created by Filip Niedzielski on 03/09/2023.
//

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int
main(int argc, char *argv[])
{
  int i = readcount();

  printf("%d\n", i);

  exit(0);
}
