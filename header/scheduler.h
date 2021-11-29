#include "./job_structure.h"

#define MAX_SIZE 20
#define MAX_TASKS 10
struct Job schedule[MAX_SIZE];

int task_index = 0;
struct Job tasks[MAX_TASKS];

//Scheduler API
    //Returns the success of adding a task, -1 FAIL, else PASS
int addTask(const struct Job job);

void removeTask(uint8_t id);

int schedulerFeasibilty();

void initScheduler();

void haltScheduler();
//End of Scheduler API

//Internals
////Runtime Scheduling
void scheduleNext();
int findAvailableTime(const struct Job job);

int isHard(const struct Job job);
////End of Runtime Scheduling


////HyperPeriod Construction
float cpuUtil();
////End of HyperPeriod Construction
//End of Internals
