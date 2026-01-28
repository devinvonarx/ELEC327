#include <ti/devices/msp/msp.h>
#include "delay.h"
#include "initialize_leds.h"
#include "state_machine_logic.h"

/* ~1 second delay at 32 MHz */
#define DELAY_1S (32000000u)

int main(void)
{
    /* Initialize pinmux + outputs + default HIGH (LEDs OFF) */
    InitializeGPIO();

    /* Start clock state */
    ClockState s = Clock_Init();

    while (1) {
        /*
         * Because LEDs are active-low:
         *   HIGH = OFF
         *   LOW  = ON
         *
         * Step 1: turn all LEDs OFF (set HIGH) safely using DOUTSET
         */
        GPIOA->DOUTSET31_0 = LED_ALL_MASK;

        /*
         * Step 2: turn ON the two “hands” (drive LOW) using DOUTCLR
         */
        GPIOA->DOUTCLR31_0 = Clock_OnMaskGPIOA(s);

        /*
         * Step 3: wait ~1 second
         */
        delay_cycles(DELAY_1S);

        /*
         * Step 4: advance the state machine
         */
        s = Clock_Next(s);
    }
}
