#include "../src/algorithm.c"
void setup() {
    algorithm_full = fcfcFull;
    algorithm_next = fcfcNext;
    contextSwitches = false;
    fullSchedule();

}

void loop() {
    scheduleNext();
    runNext();
}
