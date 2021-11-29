#include <stdio.h>
//#include "../header/scheduler.h"
#include "../src/job.c"

#define MAX_SIZE 20
#define MAX_TASKS 10
struct Job schedule[MAX_SIZE];

int task_index = 0;
struct Job tasks[MAX_TASKS];

void zeroTasks() {
    int i = 0;
    while(i < MAX_TASKS) {
        tasks[i] = (struct Job){0};
        i += 1;
    }
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
    if(task_index == MAX_SIZE) {
        return -1;
    }

    tasks[task_index] = job;
    task_index += 1;
    return 1;

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
        perror("ERROR: cpu_util is > 1");
        return -1;
    } else {
        return 1;
    }

    //check other cases
}

void printTask(const struct Job task) {
}
