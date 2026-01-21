#include "state_machine_logic.h"
#include "initialize_leds.h"   // <-- gives you LED12A, LED12B, ALL_LED_BITS_A
#include <stdint.h>

/* Active-LOW LEDs: 1 = off, 0 = on */
#define ALL_OFF_VALUE (ALL_LED_BITS_A)

/* Choose which LEDs represent ON1 and ON2 */
#define ON1_LED   LED12A
#define ON2_LED   LED12B

int GetNextState(int current_state)
{
    switch (current_state) {
        case OFF: return ON1;
        case ON1: return ON2;
        default:  return OFF;   // ON2 -> OFF (and any unexpected value)
    }
}

int GetStateOutputGPIOA(int current_state)
{
    uint32_t out = ALL_OFF_VALUE;   // start with all LEDs off (all LED bits = 1)

    switch (current_state) {
        case OFF:
            break;

        case ON1:
            out &= ~ON1_LED;        // turn LED on (active-low)
            break;

        case ON2:
            out &= ~ON2_LED;        // turn LED on (active-low)
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
