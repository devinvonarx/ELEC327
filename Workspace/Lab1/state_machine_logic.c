#include "state_machine_logic.h"
#include "initialize_leds.h"   
#include <stdint.h>

/* 1 = off and 0 = on */
#define ALL_OFF_VALUE (ALL_LED_BITS_A)

#define ON1_LED   LED12A
#define ON2_LED   LED12B

int GetNextState(int current_state)
{
    switch (current_state) {
        case OFF: return ON1;
        case ON1: return ON2;
        default:  return OFF;   
    }
}

int GetStateOutputGPIOA(int current_state)
{
    uint32_t out = ALL_OFF_VALUE;   // all LEDs start off

    switch (current_state) {
        case OFF:
            break;

        case ON1:
            out &= ~ON1_LED;        // turn LED on 
            break;

        case ON2:
            out &= ~ON2_LED;        // turn LED on 
            break;

        default:
            break;
    }

    return (int)out;
}

int GetStateOutputGPIOB(int current_state)
{
    (void)current_state;
    return 0;
}
