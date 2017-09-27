#include <Hardware/CS_Driver.h>
#include <Hardware/TIMERA_Driver.h>

Timer_A_PWMConfig PWMConfig =
{
        TIMER_A_CLOCKSOURCE_SMCLK,
        TIMER_A_CLOCKSOURCE_DIVIDER_1,
        1280,                                   /*Period of the PWM signal, CAUTION! this is based on 64 KHz signal frequency*/
        TIMER_A_CAPTURECOMPARE_REGISTER_1,
        TIMER_A_OUTPUTMODE_RESET_SET,
        64                                      /*Duty Cycle of the PWM signal, you can find the duty cycle percentage by dividing this number by the period*/
};

void main(void)
{
    MAP_WDT_A_holdTimer();
    CS_Init();
    CS_PWM_Init();
    /*Initialize TIMER_A0_BASE in PWM mode with the PWMConfig parameters. No Callback*/
    TIMERA_Init(TIMER_A0_BASE, PWM_MODE, &PWMConfig, 0x00000000);

    while(1)
    {
        /*5% Duty cycle = -90 Degrees*/
        TIMERA_DutyCycle(TIMER_A0_BASE, &PWMConfig, 64);
        __delay_cycles(20000);
        /*7.5% Duty Cycle = 0 Degrees*/
        TIMERA_DutyCycle(TIMER_A0_BASE, &PWMConfig, 96);
        __delay_cycles(20000);
        /*10% Duty Cycle = 90 Degrees*/
        TIMERA_DutyCycle(TIMER_A0_BASE, &PWMConfig, 128);
        __delay_cycles(20000);

    }
}
