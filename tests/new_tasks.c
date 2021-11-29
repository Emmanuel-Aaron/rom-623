#include "../src/scheduler.c"


int main() {
const struct TimeInfo t_info1 = createTInfo(2, 10, 4, 5, 1, 0);
const struct ExecConstraints ex_con1 = createExCons(NULL, NULL, 0, 2);
const struct Job job1 = createJob(ex_con1, t_info1, 1);

const struct TimeInfo t_info2 = createTInfo(2, 10, 4, 5, 1, 0);
const struct ExecConstraints ex_con2 = createExCons(NULL, NULL, 0, 2);
const struct Job job2 = createJob(ex_con2, t_info2, 3);

const struct Job job3 = createJob(ex_con2, t_info2, 8);

addTask(job1);
addTask(job2);
addTask(job3);

printTaskList();
removeTask(job2.ID);
printTaskList();

printf("find task id %d\nIndex: %d\n", job3.ID, findTask(job3.ID));
}
