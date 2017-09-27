# **MSP432 Servo**

This project is an PWM example project for these little [servos](https://www.amazon.com/J-Deal%C2%AE-Micro-Helicopter-Airplane-Controls/dp/B00X7CJZWM/ref=sr_1_2?ie=UTF8&qid=1506485088&sr=8-2&keywords=servos) . They are really cheap and work really great for RC projects and small robots. This project should help you develop code for different servos!
***

### **Project Setup**
***
In order to use the project you will need to have the [MSP432 SimpleLink SDK](http://www.ti.com/tool/SIMPLELINK-MSP432-SDK) library installed. To install it follow the link and select the SIMPLELINK-MSP432-SDK option, after the installation is complete import this project into Code Composer's Workspace. 

The SD Card project is divided into two folders:

- **Hardware**: This folder contains all hardware peripheral code

### **How to use it**
***
Include the following header files
```c
#include <Hardware/CS_Driver.h>
#include <Hardware/TIMERA_Driver.h>
```
Declare a global (**Really recommend to be a global variable!**) Timer A configuration variable as follows:
```c
Timer_A_PWMConfig PWMConfig =
{
        TIMER_A_CLOCKSOURCE_SMCLK,
        TIMER_A_CLOCKSOURCE_DIVIDER_1,
        1280,                                   /*Period of the PWM signal, CAUTION! this is based on 64 KHz signal frequency*/
        TIMER_A_CAPTURECOMPARE_REGISTER_1,
        TIMER_A_OUTPUTMODE_RESET_SET,
        64                                      /*Duty Cycle of the PWM signal, you can find the duty cycle percentage by dividing this number by the period*/
};
```
It is really important to emphasize that the PWM generator uses a 64 KHz clock, which means that you will have to calculate the period based on this frequency. The formula to do this is as follows:

**PWM Period = 64KHz/DesiredPWMFrequency**

Next, initialize all the necessary hardware peripherals as follows:
```c
void main()
{
    MAP_WDT_A_holdTimer();
    CS_Init();
    CS_PWM_Init();
    /*Initialize TIMER_A0_BASE in PWM mode with the PWMConfig parameters. No Callback*/
    TIMERA_Init(TIMER_A0_BASE, PWM_MODE, &PWMConfig, 0x00000000);
}
```
Change the duty cycle to move the servo motor
```c
/*5% Duty cycle = -90 Degrees*/
TIMERA_DutyCycle(TIMER_A0_BASE, &PWMConfig, 64);
__delay_cycles(20000);
/*7.5% Duty Cycle = 0 Degrees*/
TIMERA_DutyCycle(TIMER_A0_BASE, &PWMConfig, 96);
__delay_cycles(20000);
/*10% Duty Cycle = 90 Degrees*/
TIMERA_DutyCycle(TIMER_A0_BASE, &PWMConfig, 128);
__delay_cycles(20000);
```

You can also calculate the desired duty cycle integer quantity with the following formula:

**DutyCycle = (PWMPeriod * DesiredPWMDutyCycle)/100**

### **Other Details and Future Work**
***
I really want to generalize this project for any kind of servo. This will take some time and other servos to test if the idea works. I would like to implement a angle to duty cycle function for this servo project in a future iteration. 
The idea is to have global variables that will map angles to duty cycles and the programmer will take care of mapping the angles and duty cycles. The MSP432 will calculate the function that will best represent angle to duty cycle variables. Sigh! I think it should work but it will require some thought :smiley: 

***
