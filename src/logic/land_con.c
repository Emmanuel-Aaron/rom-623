#include "/root/Development/rom-623/src/system/algorithm.c"

#include "/root/Development/rom-623/src/tasks/altitude.c"
#include "/root/Development/rom-623/src/tasks/orientation.c"
#include "/root/Development/rom-623/src/tasks/clearnace.c"

void spam() {
    Serial.println(" Im the new job");
}

int tester = 0;
void checkAton() {
    Serial.println(" Im goin to delete myself soon");
    if(tester > 10) {
        const struct TimeInfo t_info5 = createTInfo(1, 10, 1, 1, 9, 0, 0);
        const struct ExecConstraints ex_con5 = createExCons(NULL, NULL, 0, 5);
        const struct Job job4 = createJob(ex_con5, t_info5, 10);

        removeTask(9);
        addTask(job4, que);
    }
    tester += 1;
}
const struct TimeInfo t_info4 = createTInfo(1, 10, 1, 1, 5, 0, 0);
const struct ExecConstraints ex_con4 = createExCons(NULL, NULL, 0, 2);
const struct Job job4 = createJob(ex_con4, t_info4, 9);
//Check if the values the sensors have recorded should invoke an 
//atonomous landing
//
//If so initiate the auatonomous landing from the autonomous_landing.c
//This event will also remove the checking for landing condition task 
//from the schedule. It will do so by adding a remove job order in 
//the schedulers que

