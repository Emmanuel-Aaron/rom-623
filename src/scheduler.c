#include <stdio.h>
//#include "../header/scheduler.h"
//#include "job.c"
#include "instructions.c"
//#include "algorithm.c"

#define MAX_SIZE 20
#define MAX_TASKS 10
#define MAX_QUE 5

struct Job* schedule[MAX_SIZE]; //List of jobs. EG. One hyperperiod
struct Job tasks[MAX_TASKS]; //List of tasks
struct Job que[MAX_QUE];

int task_index = 0; //Index for adding tasks
int job_index = 0;


void zeroQue() {
    int i = 0;
    while(i < MAX_QUE) {
        que[i] = (struct Job){0};
        i += 1;
    }
}
void zeroTasks() {
    int i = 0;
    while(i < MAX_TASKS) {
        tasks[i] = (struct Job){0};
        i += 1;
    }
}
void zeroJobs() {
    int i = 0;
    while(i < MAX_SIZE) {
        schedule[i] = (struct Job*)0;
        i += 1;
    }
}

void zero() {
    zeroJobs();
    zeroTasks();
    zeroQue();
}

int findTask(uint8_t id) {
    int i = 0;
    while (i < MAX_TASKS) {
        if(tasks[i].ID == id) {
            return i; //Task index if found
        }

        i += 1;
    }

    return -1; //If no task found -1
}

int addTask(const struct Job job) {
    int i = 0;
    while (i < MAX_TASKS) {
        if(tasks[i].ID == 0) {
            tasks[i] = job;
            return i;
        }
        i += 1;
    }
    return -1;

}

void removeTask(uint8_t id) {
    int index = findTask(id);
    tasks[index] = (const struct Job){0}; //write entire task to 0
    //restructureTasks();
}

void printTaskList() {
    int i = 0;
    while (i < MAX_TASKS) {
        printf("Task id: %d\n", tasks[i].ID);
        i += 1;
    }
}


float cpuUtil() {
    float cpu_util = 0;

    int i = 0;
    while(i < MAX_TASKS) {
        if(tasks[i].ID == 0) {
        } 
        else if(tasks[i].t_info.period == 0 || tasks[i].t_info.exec_time == 0) {
            return 1; //Task list contains impossible tasks
        } 
        else{
            float period = tasks[i].t_info.period;
            float exec_t = tasks[i].t_info.exec_time;
            cpu_util += (exec_t/period);
        }
        i += 1;
    }

    return cpu_util;
}

int schedulerFeasibilty() {
    float cpu_util = cpuUtil();

    if(cpu_util >= 1) {
        printf("CPU_UTIL: %f\n", cpu_util);
        return -1;
    } else {
        return 1;
    }

    //check other cases
}

//Reschedule all the jobs
void runNext() {
    if(schedule[job_index] == 0) {
    }
    else {
    void (*func_ptr)(void) = getInstructions(*schedule[job_index]);
    func_ptr();
    }
    job_index = (job_index + 1)%MAX_SIZE;
}

void printTask(const struct Job task) {
}
