#include "/root/Development/rom-623/src/logic/land_con.c"


int hard;
void setup() {
Serial.begin(9600);
    //JOB1
    //Exec, prio, period, periodic, deadl, dead_t, realease
    const struct TimeInfo t_info1 = createTInfo(1, 10, 4, 3, 1, 1, 0);

    //ptr, ptr, interuptable, func_type
    const struct ExecConstraints ex_con1 = createExCons(NULL, NULL, 0, 1);

    const struct Job job1 = createJob(ex_con1, t_info1, 1);

    //JOB2
    const struct TimeInfo t_info2 = createTInfo(1, 10, 1, 1, 2, 0, 0);
    const struct ExecConstraints ex_con2 = createExCons(NULL, NULL, 0, 2);
    const struct Job job2 = createJob(ex_con2, t_info2, 6);

    //JOB3
    const struct TimeInfo t_info3 = createTInfo(1, 10, 2, 1, 3, 0, 0);
    const struct ExecConstraints ex_con3 = createExCons(NULL, NULL, 0, 3);
    const struct Job job3 = createJob(ex_con3, t_info3, 8);

    //JOB4
    const struct TimeInfo t_info4 = createTInfo(1, 10, 1, 1, 5, 0, 0);
    const struct ExecConstraints ex_con4 = createExCons(NULL, NULL, 0, 4);
    const struct Job job4 = createJob(ex_con4, t_info4, 9);

    //Setting the instructions for the jobs
    //func_type, func_ptr
    addInstruction(1, altitude);
    addInstruction(2, orient);
    addInstruction(3, groundClearance);
    addInstruction(4, checkAton);
    addInstruction(5, spam);


    //Zeroing all lists
    zero();
    //Adding the tasks
    addTask(job1, que);
    addTask(job2, que);
    addTask(job3, que);
    addTask(job4, que);

    //chacking if the schudle is feasible
    //printf("Is feasible: %d\n", schedulerFeasibilty());

    //setting the desired algorithms
    algorithm_full = edfFull;
    algorithm_next = edfFull;

    //Making a full jobs schedule from tasks
    fullSchedule();
    hard = 0;

}

void loop() {
    scheduleNext(hard);
    runNext();
}
