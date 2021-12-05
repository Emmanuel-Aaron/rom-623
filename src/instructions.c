#include "job.c"

#define MAX_INST 10

void (*instructions[MAX_INST]) (void);

void addInstruction(int index, void (*func_ptr)(void)) {
    instructions[index] = func_ptr;
}

void* getInstructions(struct Job job) {
    return instructions[job.ex_con.instructions];
}

