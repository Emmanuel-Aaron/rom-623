void (*job)(void*);
void* job_data;


void setJob(void (*func_ptr)(void*), void* func_data) {
    job = func_ptr;
    job_data = func_data;
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

void setJobTime(void (*func_ptr)(void*), void* func_data, int r_deadline) {
    setJob(func_ptr, func_data);
    setIntTimer(r_deadline);
}

ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
    //generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
    TIMSK1 = 0;
    //setNextJob();
    job(job_data);
}
