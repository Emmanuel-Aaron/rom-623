struct Task {
};

struct HyperPeriod {
    struct HyperPeriod* next;
    struct HyperPeriod* prev;

    struct Task job;

};

struct HyperPeriod* schedule;

//Scheduler API
void addTask(struct Task task);

void removeTask(int id);

bool schedulerFeasibilty();

void initScheduler();

void haltScheduler();
//End of Scheduler API

//Internals
////Runtime Scheduling
void schedule();

bool isHard(struct Task job);
////End of Runtime Scheduling


////HyperPeriod Construction
float cpuUtil();
////End of HyperPeriod Construction
//End of Internals
