/**
 * lab1.c
 * 
 * Main program for LED clock
 * Updates LED positions every second to simulate clock behavior
 */

#include <ti/devices/msp/msp.h>
#include "delay.h"
#include "initialize_leds.h"
#include "state_machine_logic.h"

/* 
 * Delay for approximately 1 second at 32 MHz CPU_CLK
 * Adjust this value to achieve exactly 1 second timing
 */
#define DELAY (32000000)

int main(void)
{
    /* Initialize all GPIO pins for LEDs */
    InitializeGPIO();

    int state = 0;  /* State variable for compatibility */

    /* Main loop - runs forever, updating clock every second */
    while (1) {
        /* Get output pattern for GPIOA */
        int output = GetStateOutputGPIOA(state);

        /* Update GPIO outputs */
        GPIOA->DOUT31_0 = output;

        /* Advance to next state (increment counters) */
        state = GetNextState(state);

        /* Wait 1 second before next update */
        delay_cycles(DELAY);
    }
}

/* 
 * Copyright (c) 2023, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * * Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */