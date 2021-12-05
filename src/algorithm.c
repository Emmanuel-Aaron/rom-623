//time = millis();
//#include "./job.c"
#include "./scheduler.c"
#include "./arduino/interupt/interupt.h"

void (*algorithm_full)(void); //The schedulers algorithm
void (*algorithm_next)(void); //The schedulers algorithm

void printJobs() {
    int i = 0;
    while(i < MAX_SIZE) {
        if(schedule[i] == 0) {}
        else {
        printf("Trying to print info\n");
            printf("Period: %ld\n", schedule[i]->t_info.period);
        }
        i += 1;
    }
}

void printPtrList(struct Job** ptr_list, int size) {
    int i = 0;
    while(i < size) {
        printf("Index: %d, ID: %d, Deadline: %ld, Period: %ld\n",i, ptr_list[i]->ID, ptr_list[i]->t_info.deadline, ptr_list[i]->t_info.period);
        i += 1;
    }
}

void copyPtrList(struct Job* list, struct Job** ptr_list, int size) {
    int i = 0;
    while (i < size) {
        ptr_list[i] = &list[i];
        i += 1;
    }
}

void copyList(struct Job** src, struct Job** dest, int size) {
    int i = 0;
    while ( i < size) {
        if(src[i]->ID == 0) {}
        else {
            dest[i] = src[i];
        }
        i += 1;
    }
}

void fullSchedule() {
    algorithm_full();
}

//sets the next hard deadline
void setNextHardD() {
    int i = job_index;
    while(i < (i + MAX_SIZE)) {
        if(schedule[i%MAX_SIZE] == 0) {}
        else if(schedule[i%MAX_SIZE]->t_info.deadline_type == 1) {
            setIntTimer(2);
            instr = instructions[schedule[i%MAX_SIZE]->ex_con.instructions];
        }
    }
}

void scheduleNext(int hard) {
    if(hard != 0) {
        //Set the next interupt
        //setNextHardD();
    }
    algorithm_next();
}

int findAvailableTime(struct Job* job_ptr) {
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

//Must account for release time!!!!!!!!!
//Emanuels algorithem
void edfFull() {
    struct Job* ptr_list[MAX_TASKS];
    copyPtrList(tasks, ptr_list, MAX_TASKS);

    int j = 0;
    while(j < MAX_TASKS) {

        int i = 0;
        struct Job* temp;
        while (i < (MAX_TASKS - j)) {
            if(ptr_list[j + i]->ID == 0) {}
            else if(ptr_list[j + i]->t_info.deadline < ptr_list[j]->t_info.deadline) {
                temp = ptr_list[j + i];
                ptr_list[j + i] = ptr_list[j];
                ptr_list[j] = temp;
            }
            i += 1;
        }

        j += 1;
    }

    copyList(ptr_list, schedule, MAX_TASKS);
}

void periodSFull(){
    int i = 0;

    struct Job* hold;
    struct Job* Holder[MAX_TASKS];

    while (i < MAX_TASKS){
        if(tasks[i].ID == 0){
        }
        else{
            for(int cp = 0; cp < MAX_TASKS; cp++){
                Holder[cp] = &tasks[cp];
            }

            for(int k = 0; k < MAX_TASKS; k++){
                for(int n = 0; n < MAX_TASKS; n++){
                    if(Holder[k]->t_info.period > Holder[n]->t_info.period){
                        continue;
                    }
                    else{
                        hold = Holder[k];
                        Holder[k] = Holder[n];
                        Holder[n] = hold;
                    }
                }
            }
            schedule[i] = Holder[i];
        }
        i++;
    }
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

void fcfcNext() {
    addQue();
    fcfcFull();
}

