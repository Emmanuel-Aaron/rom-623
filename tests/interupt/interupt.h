struct Interupt {
    bool ready;
    size_t start_time;
    void (*job)(void*);
    void* job_data;
};

const int max_size = 15;
Interupt interupt_que[max_size];
int interupt_index = 0;
int job_index = 0;

void (*job)(void*);
void* job_data;


void addJob2Que(void (*func_ptr)(void*), void* func_data, int start_time) {
    struct Interupt interrupt;
    interrupt.start_time = start_time;
    interrupt.job_data = func_data;
    interrupt.job = func_ptr;
    interrupt.ready = false;


    //Error handling if Job overwright
    interupt_que[job_index] = interrupt;
    job_index = (job_index % max_size) + 1;
}

void runJob() {
    Interupt interupt = interupt_que[interupt_index];
    interupt.job(interupt.job_data);
}


int compValue(double clock_freq, int prescale, int seconds) {
    return ( clock_freq / (prescale * (1000/seconds)) ) - 1;
}

void setIntTimer(int seconds) {
    double clock_freq = 16000000;
    int prescale = 1;

    cli();//stop interrupts

    //set timer1 interrupt at 1Hz
    TCCR1A = 0;// set entire TCCR1A register to 0
    TCCR1B = 0;// same for TCCR1B
    TCNT1  = 0;//initialize counter value to 0

    OCR1A = compValue(clock_freq, prescale, seconds);// = (16*10^6) / (1*1024) - 1 (must be <65536)

    // turn on CTC mode
    TCCR1B |= (1 << WGM12);
    // Set CS12 and CS10 bits for 1024 prescaler
    TCCR1B |= (1 << CS12) | (1 << CS10);  
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);


    sei();//allow interrupts
}

int nextActiveJob() {
    int i = 0;
    while(i < max_size) {
        if(interupt_que[interupt_index].ready = false) {
            i += 1;
            interupt_index = (interupt_index % max_size) + 1;
    return -1;
        }
        else {
            return interupt_index;
        }
    }

}
void setNextJob() {
    if(nextActiveJob() == -1) {
    Serial.print("NoJob\n");
        return;
    } else {
    Serial.print("IsActiveJob\n");
    int start_time = interupt_que[interupt_index].start_time; //Has to be relative, is currently absolute
    Serial.print(start_time);
        digitalWrite(10, HIGH);
        delay(100);
        digitalWrite(10, LOW);
    setIntTimer(start_time);
    }
}

void removeCurrentJob() {
    interupt_que[interupt_index].ready = false;
}

ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
    //generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
    TIMSK1 = 0;
    TCCR1A = 0;// set entire TCCR1A register to 0
    TCCR1B = 0;// same for TCCR1B
    TCNT1  = 0;//initialize counter value to 0
        digitalWrite(5, HIGH);
        delay(180);
        digitalWrite(5, LOW);
        delay(180);
    removeCurrentJob();
    runJob();
    Serial.print("Interupt\n");


    interupt_index = (interupt_index % max_size) + 1;
    //setNextJob();
    //
}

void startHardSchedular() {
    interupt_index = 0;
    setNextJob();
    return;
}
