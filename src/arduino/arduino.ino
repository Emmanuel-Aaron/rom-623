#include "/root/Development/rom-623/src/system/algorithm.c"

#include "/root/Development/rom-623/src/tasks/altitude.c"
#include "/root/Development/rom-623/src/tasks/orientation.c"


void printer1() {
    digitalWrite(11, HIGH);
    delay(1000);
    digitalWrite(11, LOW);
    delay(1000);
}

void printer2() {
    digitalWrite(10, HIGH);
    delay(2000);
    digitalWrite(10, LOW);
    delay(1000);
}

int hard;
void setup() {
Serial.begin(9600);
    //JOB1
    //Exec, prio, period, deadl, dead_t, realease
    const struct TimeInfo t_info1 = createTInfo(1, 10, 4, 7, 1, 0);

    //ptr, ptr, interuptable, func_type
    const struct ExecConstraints ex_con1 = createExCons(NULL, NULL, 0, 1);

    const struct Job job1 = createJob(ex_con1, t_info1, 1);

    //JOB2
    const struct TimeInfo t_info2 = createTInfo(1, 10, 2, 6, 0, 0);
    const struct ExecConstraints ex_con2 = createExCons(NULL, NULL, 0, 2);
    const struct Job job2 = createJob(ex_con2, t_info2, 6);

    //Setting the instructions for the jobs
    addInstruction(1, altitude);
    addInstruction(2, orient);


    //Zeroing all lists
    zero();
    //Adding the tasks
    addTask(job1);
    addTask(job2);

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
