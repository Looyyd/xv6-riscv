//
// Created by Filip Niedzielski on 14/09/2023.
//

#ifndef XV6_RISCV_RAND_H
#define XV6_RISCV_RAND_H
// Constants for the LCG (values taken from Numerical Recipes)
#define LCG_A 1664525
#define LCG_C 1013904223
#define LCG_M 4294967296 // 2^32

static unsigned long lcg_seed = 12345678; // Initial seed

unsigned long kernel_rand(void) {
    lcg_seed = (LCG_A * lcg_seed + LCG_C) % LCG_M;
    return lcg_seed;
}

void kernel_srand(unsigned long seed) {
    lcg_seed = seed;
}


#endif //XV6_RISCV_RAND_H
