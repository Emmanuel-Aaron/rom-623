#include "/root/Development/rom-623/src/tasks/logic/aton_landing.c"


int hard;
void setup() {

//setuping up motors
aileronL.attach(2);
aileronR.attach(4);
elevator.attach(6);
esc.attach(12);
arm();

//Possible serial output for testing
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

    //JOB4 preflight
        const struct TimeInfo t_info4 = createTInfo(1, 10, 1, 1, 10, 0, 0);
        const struct ExecConstraints ex_con4 = createExCons(NULL, NULL, 0, 4);
        const struct Job job4 = createJob(ex_con4, t_info4, 11);

    //Setting the instructions for the jobs
    //func_type, func_ptr
    addInstruction(1, altitude);
    addInstruction(2, orient);
    addInstruction(3, groundClearance);
    addInstruction(4, postTransFlight);
    addInstruction(5, preTransFlight);


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
