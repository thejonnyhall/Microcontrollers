void TimerInit(void)
{
//Set to Normal Timer Mode using TCCR0B
    TCCR0B &= ~((1<<WGM02));
    //Set Prescaler using TCCR0B, using Clock Speed find timer speed = 1/(Clock Speed/Prescaler)
    //Prescaler = 1024
    //Timer Speed = 128 microseconds
    //Timer Overflow Speed = 32640 micro seconds (Timer Speed * 255) - (255 since 8-bit timer)
    TCCR0B |= (1<<CS02)|(1<<CS00);
    TCCR0B &= ~((1<<CS01));
}