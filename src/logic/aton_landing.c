//Preform an autonomous landing by correcting the planes oriatation 
//and altitude to land on the ground
//
#include "/root/Development/rom-623/src/system/algorithm.c"

#include "/root/Development/rom-623/src/tasks/altitude.c"
#include "/root/Development/rom-623/src/tasks/orientation.c"
#include "/root/Development/rom-623/src/tasks/clearnace.c"
#include "/root/Development/rom-623/src/sensors/brushlessMotor/motor.c"


double trans_altitude = 1;

double pre_trans_roll = 0;
double pre_trans_pitch = 12;

double post_trans_roll = 0;
double post_trans_pitch = 8;

double altitude_error = 2;
double angle_error;
double ajust_factor;


void holdRoll(double roll) {
    if(current_ort.roll < (roll - angle_error)) {
        aileronL.write(130);
        delay(100);
        aileronR.write(60);
        delay(100);
    } 
    else if(current_ort.roll > (roll + angle_error)) {
        aileronL.write(55);
        delay(100);
        aileronR.write(130);
        delay(100);
    }
    else {
    }
}

void holdPitch(double pitch) {
    if(current_ort.pitch < (pitch - angle_error)) {
        elevator.write(130);
        delay(100);
    } 
    else if(current_ort.pitch > (pitch + angle_error)) {
        elevator.write(60);
        delay(100);
    }
    else {
    }
}

void holdOrientation(double pitch, double roll) {
    holdPitch(pitch);
    holdRoll(roll);
}

int room = 0;
//Task 12
void postTransFlight() {
    if(room == 0) {
        Serial.println("Motor on");
        motorStart();
        motorUp();
        room = 1;
    }
    Serial.println("Post trans flight");
    if(clearance > trans_altitude) {
        const struct TimeInfo t_info7 = createTInfo(1, 10, 1, 1, 10, 0, 0);
        const struct ExecConstraints ex_con7 = createExCons(NULL, NULL, 0, 4);
        const struct Job job7 = createJob(ex_con7, t_info7, 11);

        removeTask(12);
        addTask(job7, que);
    } else {

        holdOrientation(post_trans_pitch, post_trans_roll);
    }
}

int roon = 0;
//task 11
void preTransFlight() {
    if(roon == 0) {
        Serial.println("Motor Low");
        motorDown();
        roon = 1;
    }
    Serial.println("Pre trans flight");
    if((current_altitude) < trans_altitude) {
        const struct TimeInfo t_info6 = createTInfo(1, 10, 1, 1, 11, 0, 0);
        const struct ExecConstraints ex_con6 = createExCons(NULL, NULL, 0, 5);
        const struct Job job6 = createJob(ex_con6, t_info6, 12);

        removeTask(11);
        addTask(job6, que);
    } else {
        holdOrientation(pre_trans_pitch, pre_trans_roll);
    }
}
