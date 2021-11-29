#include "./job_structure.h"
#include <stdio.h>

void printJob(struct Job job) {
    struct ExecConstraints ex_cons = job.ex_con;
    printf("---Execution Constraints---\n");
    printf("dependent jobs: %d\n", ex_cons.dependent_jobs);
    printf("resources: %d\n", ex_cons.resources);
    printf("interuptable: %d\n", ex_cons.interuptable);
    printf("instructions: %d\n", ex_cons.instructions);
    printf("\n");

    struct TimeInfo t_info = job.t_info;
    printf("---TimeInfo---\n");
    printf("release: %ld\n", t_info.release);
    printf("exec: %ld\n", t_info.exec_time);
    printf("priority: %d\n", t_info.priority);
    printf("periodic: %d\n", t_info.periodic);
    printf("period: %ld\n", t_info.period);
    printf("deadline: %ld\n", t_info.deadline);
    printf("deadline type: %d\n", t_info.deadline_type);
    printf("\n");
};

