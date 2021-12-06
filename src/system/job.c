#include "../../header/job_structure.h"
//#include "../header/test_resources.h"

//Will return a uniqe deterministic ID for each job
uint8_t genID(struct Job job) {
    uint8_t job_id = 1;
    return job_id;
}

const struct TimeInfo createTInfo(size_t exec_t, uint8_t prio, size_t period, uint8_t periodic, size_t deadl, uint8_t deadl_t, size_t release) {
    struct TimeInfo t_info;

        t_info.exec_time = exec_t;
        t_info.priority = prio;
        t_info.period = period;
        t_info.deadline = deadl;
        t_info.deadline_type = deadl_t;
        t_info.release = release;
        t_info.periodic = periodic;

    return t_info;
}

const struct ExecConstraints createExCons(void* d_jobs, void* res, uint8_t interupt, uint8_t instr) {
    struct ExecConstraints ex_con;

        ex_con.dependent_jobs = d_jobs;
        ex_con.resources = res;
        ex_con.interuptable = interupt;
        ex_con.instructions = instr;

    return ex_con;
}

const struct Job createJob(struct ExecConstraints ex_con, struct TimeInfo t_info, uint8_t id) {
    struct Job job;

    job.ex_con = ex_con;
    job.t_info = t_info;
    job.ID = id;

    return job;
}
