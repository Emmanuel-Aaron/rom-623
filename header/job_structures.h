#include "./job_strcuture.h"

struct JobList {
    uint8_t dynamic; //0||!0
    struct Job* jobs; //List of jobs
};

//Does heap or stack
struct Job* createJobList(uint8_t dynamic, );

void addJob(struct Job job);

//Avoid using as jobs could reapear and removing is waste of memory 
//and computation
void removeJob(struct Job job, uint8_t id); //Job or ID can be used NOT BOTH

