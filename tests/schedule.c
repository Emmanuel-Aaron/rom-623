#include "../src/algorithm.c"

void printer1() {
    printf("Im Job 1\n");
}


void printer2() {
    printf("Im Job 2\n");
}

int main() {


    //JOB1
    //Exec, prio, period, deadl, dead_t, realease
    const struct TimeInfo t_info1 = createTInfo(1, 10, 4, 1, 1, 0);

    //ptr, ptr, interuptable, func_type
    const struct ExecConstraints ex_con1 = createExCons(NULL, NULL, 0, 1);

    const struct Job job1 = createJob(ex_con1, t_info1, 1);

    //JOB2
    const struct TimeInfo t_info2 = createTInfo(1, 10, 2, 2, 1, 0);
    const struct ExecConstraints ex_con2 = createExCons(NULL, NULL, 0, 2);
    const struct Job job2 = createJob(ex_con2, t_info2, 6);

    //Setting the instructions for the jobs
    addInstruction(1, printer1);
    addInstruction(2, printer2);


    //Zeroing all lists
    zero();
    //Adding the tasks
    addTask(job1);
    addTask(job2);
    edfFull();

    //chacking if the schudle is feasible
    printf("Is feasible: %d\n", schedulerFeasibilty());

    //setting the desired algorithms
    algorithm_full = edfFull;
    algorithm_next = edfFull;
    //contextSwitches = false;

    //Making a full jobs schedule from tasks
    fullSchedule();
    printJobs();
    printf("Scheduled1\n");

    //Loop runnin jobs with the selected algorithms
   while (1) {
       scheduleNext();
       runNext();
   }
}


