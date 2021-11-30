#include "../src/algorithm.c"

//

int main() {
    //Exec, prio, period, deadl, dead_t, realease
const struct TimeInfo t_info1 = createTInfo(1, 10, 3, 5, 1, 0);

    //ptr, ptr, interuptable, func_type
const struct ExecConstraints ex_con1 = createExCons(NULL, NULL, 0, 2);


const struct Job job1 = createJob(ex_con1, t_info1, 1);

const struct TimeInfo t_info2 = createTInfo(1, 10, 2, 5, 1, 0);
const struct ExecConstraints ex_con2 = createExCons(NULL, NULL, 0, 2);
const struct Job job2 = createJob(ex_con2, t_info2, 6);

const struct TimeInfo t_info3 = createTInfo(1, 10, 1, 5, 1, 0);
const struct ExecConstraints ex_con3 = createExCons(NULL, NULL, 0, 2);
const struct Job job3 = createJob(ex_con3, t_info3, 3);

zeroTasks();
addTask(job1);
addTask(job2);
addTask(job3);

//removeTask(job2.ID);
printTaskList();
printf("Jobs--Below\n");
periodFull();
printJobs();

printf("Is feasible: %d\n", schedulerFeasibilty());

printf("find task id %d\nIndex: %d\n", job3.ID, findTask(job3.ID));
}
