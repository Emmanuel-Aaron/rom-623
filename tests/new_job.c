#include "../src/job.c"

int main() {
const struct TimeInfo t_info = createTInfo(2, 10, 4, 5, 1, 0);
const struct ExecConstraints ex_con = createExCons(NULL, NULL, 0, 2);
const struct Job job1 = createJob(ex_con, t_info, 0);

printJob(job1);
}
