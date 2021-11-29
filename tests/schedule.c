#include "../src/algorithm.c"

void printer1() {
    printf("Im Job 1\n");
}

void printer2() {
    printf("Im Job 2\n");
}

int main() {

addInstruction(1, printer1);
addInstruction(2, printer2);
    //Exec, prio, period, deadl, dead_t, realease
const struct TimeInfo t_info1 = createTInfo(1, 10, 4, 5, 1, 0);

    //ptr, ptr, interuptable, func_type
const struct ExecConstraints ex_con1 = createExCons(NULL, NULL, 0, 1);

const struct Job job1 = createJob(ex_con1, t_info1, 1);

const struct TimeInfo t_info2 = createTInfo(1, 10, 2, 5, 1, 0);
const struct ExecConstraints ex_con2 = createExCons(NULL, NULL, 0, 2);
const struct Job job2 = createJob(ex_con2, t_info2, 6);


zero();
addTask(job1);
addTask(job2);
printf("Is feasible: %d\n", schedulerFeasibilty());

    algorithm_full = fcfcFull;
    algorithm_next = fcfcNext;
    //contextSwitches = false;
    fullSchedule();

    while (1) {
        scheduleNext();
        runNext();
    }
}


