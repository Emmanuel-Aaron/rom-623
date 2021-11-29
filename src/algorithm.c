//time = millis();
//#include "./job.c"
#include "./scheduler.c"

void (*algorithm_full)(void); //The schedulers algorithm
void (*algorithm_next)(void); //The schedulers algorithm

void fullSchedule() {
    algorithm_full();
}

void scheduleNext() {
    algorithm_next();
}

int findAvailableTime(struct Job* job_ptr) {
}



void fcfcFull() {
    int i = 0;
    while (i < MAX_TASKS) {
        if(tasks[i].ID == 0) {
        }
        else {
            schedule[i] = &tasks[i];
        }

        i += 1;
    }
}

int addQue() {
    int i = 0;
    while (i < MAX_QUE) {
        if (task_index == MAX_QUE) {
            return -1;
        }
        else if (que[i].ID == 0) {}
        else {
            addTask(que[i]);
            que[i] = (struct Job){0};
        }
        i += 1;
    }
    return 1;
}

void fcfcNext() {
    addQue();
    fcfcFull();
}
