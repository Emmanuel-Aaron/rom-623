//Arduino specific values!!!!
//

void (*instr)(void);

int compValue(double clock_freq, int prescale, int milliseconds) {
    return ( clock_freq / (prescale * (1000000/milliseconds)) ) - 1;
}

void oldInterupt(int milliseconds) {
    double clock_freq = 16000000;
    int prescale = 1;

    cli();//stop interrupts

    //set timer1 interrupt at 1Hz
    TCCR2A = 0;// set entire TCCR1A register to 0
    TCCR2B = 0;// same for TCCR1B
    TCNT2  = 0;//initialize counter value to 0

    OCR2A = compValue(clock_freq, prescale, milliseconds);// = (16*10^6) / (1*1024) - 1 (must be <65536)

    // turn on CTC mode
    TCCR2B |= (1 << WGM12);
    // Set CS12 and CS10 bits for 1024 prescaler
    TCCR2B |= (1 << CS12) | (1 << CS10);  
    // enable timer compare interrupt
    TIMSK2 |= (1 << OCIE2A);


    sei();//allow interrupts
}

void setIntTimer(int milliseconds) {
    OCR2A = 65530;
    TIMSK2 |= _BV(OCIE2A);
}

void freezeTimer() {
    cli();//stop interrupts
   TIMSK2 = 0;
//   TCCR2A = 0;// set entire TCCR1A register to 0
//   TCCR2B = 0;// same for TCCR1B
//   TCNT2  = 0;//initialize counter value to 0
}


ISR(TIMER2_COMPA_vect){
    //freezeTimer();
    cli();//stop interrupts
   TIMSK1 = 0;
    digitalWrite(5, HIGH);
    delay(1000);
    digitalWrite(5, LOW);
    delay(200);
    //instr();
}
