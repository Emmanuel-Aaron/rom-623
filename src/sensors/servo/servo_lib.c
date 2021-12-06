#include "/root/Development/rom-623/src/sensors/servo/Servo.cpp"

double actual_Laileron_pos = 0;
double actual_Raileron_pos = 0;
double actual_elevator_pos = 0;

Servo aileronL;
Servo aileronR;
Servo elevator;


void wingletZero(){

    aileronL.write(86);
    aileronR.write(90);
    elevator.write(90);
}
    

//Non inverted control of ailarons and elevator
void adjustPitch(double relative_angle) {

    actual_Laileron_pos += relative_angle;
    actual_Raileron_pos += relative_angle;
    actual_elevator_pos += relative_angle;
    
    if(actual_Laileron_pos < 55 || actual_Raileron_pos < 55 || actual_elevator_pos < 60){
    
        actual_Laileron_pos -= relative_angle;
        actual_Raileron_pos -= relative_angle;
        actual_elevator_pos -= relative_angle;
    }
    
    else if(actual_Laileron_pos > 130 || actual_Raileron_pos > 130 || actual_elevator_pos > 125){
        
        actual_Laileron_pos -= relative_angle;
        actual_Raileron_pos -= relative_angle;
        actual_elevator_pos -= relative_angle;
    }
    else{
        elevator.write(actual_elevator_pos);
        aileronL.write(180 - actual_Laileron_pos);
        aileronR.write(actual_Raileron_pos);
    }
}

//Inverted Control of ailarons
//NO control of elevator
void adjustRoll(int relative_angle) {
    

    actual_Laileron_pos += relative_angle;
    actual_Raileron_pos += relative_angle;
    
    if(actual_Laileron_pos < 55 || actual_Raileron_pos < 55 || actual_elevator_pos < 60){
    
        actual_Laileron_pos -= relative_angle;
        actual_Raileron_pos -= relative_angle;
    }
    
    else if(actual_Laileron_pos > 130 || actual_Raileron_pos > 130 || actual_elevator_pos > 125){
        
        actual_Laileron_pos -= relative_angle;
        actual_Raileron_pos -= relative_angle;
    }
    else{
        elevator.write(actual_elevator_pos);
        aileronL.write(actual_Laileron_pos);
    }

}

