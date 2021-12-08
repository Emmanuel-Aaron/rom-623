#include <stdint.h>
#include <stddef.h>
//Information regarding time
struct TimeInfo {
    uint8_t priority; //0-10

    size_t release;
    size_t exec_time; //Milliseconds

    uint8_t periodic; //0||!0
    size_t period; //Milliseconds

    size_t deadline; //Relative Milliseconds
    uint8_t deadline_type; //0-4
};

struct ExecConstraints {
    void* dependent_jobs; //List of Task ID's
    void* resources; //List of resource ID's

    uint8_t interuptable; //0||!0
    uint8_t instructions; //Task function(s)
};

struct Job {
    uint8_t ID;

    struct ExecConstraints ex_con;
    struct TimeInfo t_info;
};

//Group of jobs which should be treated as one
struct Mash {
    uint8_t ID;

    //List fo Jobs in the Mash
    struct Job* jobs;
    uint8_t num_jobs;

    //Combined result of all jobs for Mash
    struct ExecConstraints ex_con;
    struct TimeInfo t_info;
};

//Preforms required conversions and calculations to create time info
const struct TimeInfo createTInfo(size_t exec_t, uint8_t prio, size_t period, uint8_t periodic, size_t deadl, uint8_t deadl_t, size_t release);

//Preforms required conversions and calculations to create exec 
//constraints
const struct ExecConstraints createExCons(void* d_jobs, void* res, uint8_t interupt, uint8_t instr);

const struct Job createJob(struct ExecConstraints ex_con, struct TimeInfo t_info, uint8_t id);

