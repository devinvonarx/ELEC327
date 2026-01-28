#include "state_machine_logic.h"
#include "initialize_leds.h"
#include <ti/devices/msp/msp.h>

void stateMachine(int state_A, int state_B) { 
    // LED B FSM: inner loop
    switch(state_B) {
        case LED12B_state:
            GPIOA->DOUTCLR31_0 = LED12B_bit; // turn LED12B on 
            GPIOA->DOUTSET31_0 = LED11B_bit; // turn prev LED (LED11B) off
            state_B = LED1B_state; // store state_B's next state (LED1B)
            break;
        case LED1B_state:
            GPIOA->DOUTCLR31_0 = LED1B_bit;
            GPIOA->DOUTSET31_0 = LED12B_bit;
            state_B = LED2B_state;
            break;
        case LED2B_state:
            GPIOA->DOUTCLR31_0 = LED2B_bit;
            GPIOA->DOUTSET31_0 = LED1B_bit;
            state_B = LED3B_state;
            break;
        case LED3B_state:
            GPIOA->DOUTCLR31_0 = LED3B_bit;
            GPIOA->DOUTSET31_0 = LED2B_bit;
            state_B = LED4B_state;
            break;
        case LED4B_state:
            GPIOA->DOUTCLR31_0 = LED4B_bit;
            GPIOA->DOUTSET31_0 = LED3B_bit;
            state_B = LED5B_state;
            break;
        case LED5B_state:
            GPIOA->DOUTCLR31_0 = LED5B_bit;
            GPIOA->DOUTSET31_0 = LED4B_bit;
            state_B = LED6B_state;
            break;
        case LED6B_state:
            GPIOA->DOUTCLR31_0 = LED6B_bit;
            GPIOA->DOUTSET31_0 = LED5B_bit;
            state_B = LED7B_state;
            break;
        case LED7B_state:
            GPIOA->DOUTCLR31_0 = LED7B_bit;
            GPIOA->DOUTSET31_0 = LED6B_bit;
            state_B = LED8B_state;
            break;
        case LED8B_state:
            GPIOA->DOUTCLR31_0 = LED8B_bit;
            GPIOA->DOUTSET31_0 = LED7B_bit;
            state_B = LED9B_state;
            break;
        case LED9B_state:
            GPIOA->DOUTCLR31_0 = LED9B_bit;
            GPIOA->DOUTSET31_0 = LED8B_bit;
            state_B = LED10B_state;
            break;
        case LED10B_state:
            GPIOA->DOUTCLR31_0 = LED10B_bit;
            GPIOA->DOUTSET31_0 = LED9B_bit;
            state_B = LED11B_state;
            break;
        case LED11B_state:
            GPIOA->DOUTCLR31_0 = LED11B_bit;
            GPIOA->DOUTSET31_0 = LED10B_bit;
            state_B = LED12B_state;
            break;
        default:
            state_B = LED12B_state;
            break;
    }

    // LED A FSM (advance only when B wraps): outer loop
    if(state_B == LED1B_state) { // wrap case
        switch(state_A) {
            case LED12A_state:
                GPIOA->DOUTCLR31_0 = LED12A_bit; // turn on LED12A
                GPIOA->DOUTSET31_0 = LED11A_bit; // turn off prev LED 
                state_A = LED1A_state; // store state_A's next state
                break;
            case LED1A_state:
                GPIOA->DOUTCLR31_0 = LED1A_bit;
                GPIOA->DOUTSET31_0 = LED12A_bit;
                state_A = LED2A_state;
                break;
            case LED2A_state:
                GPIOA->DOUTCLR31_0 = LED2A_bit;
                GPIOA->DOUTSET31_0 = LED1A_bit;
                state_A = LED3A_state;
                break;
            case LED3A_state:
                GPIOA->DOUTCLR31_0 = LED3A_bit;
                GPIOA->DOUTSET31_0 = LED2A_bit;
                state_A = LED4A_state;
                break;
            case LED4A_state:
                GPIOA->DOUTCLR31_0 = LED4A_bit;
                GPIOA->DOUTSET31_0 = LED3A_bit;
                state_A = LED5A_state;
                break;
            case LED5A_state:
                GPIOA->DOUTCLR31_0 = LED5A_bit;
                GPIOA->DOUTSET31_0 = LED4A_bit;
                state_A = LED6A_state;
                break;
            case LED6A_state:
                GPIOA->DOUTCLR31_0 = LED6A_bit;
                GPIOA->DOUTSET31_0 = LED5A_bit;
                state_A = LED7A_state;
                break;
            case LED7A_state:
                GPIOA->DOUTCLR31_0 = LED7A_bit;
                GPIOA->DOUTSET31_0 = LED6A_bit;
                state_A = LED8A_state;
                break;
            case LED8A_state:
                GPIOA->DOUTCLR31_0 = LED8A_bit;
                GPIOA->DOUTSET31_0 = LED7A_bit;
                state_A = LED9A_state;
                break;
            case LED9A_state:
                GPIOA->DOUTCLR31_0 = LED9A_bit;
                GPIOA->DOUTSET31_0 = LED8A_bit;
                state_A = LED10A_state;
                break;
            case LED10A_state:
                GPIOA->DOUTCLR31_0 = LED10A_bit;
                GPIOA->DOUTSET31_0 = LED9A_bit;
                state_A = LED11A_state;
                break;
            case LED11A_state:
                GPIOA->DOUTCLR31_0 = LED11A_bit;
                GPIOA->DOUTSET31_0 = LED10A_bit;
                state_A = LED12A_state;
                break;
            default:
                state_A = LED12A_state;
                break;
        }
    }

    curr_states.state_A = state_A; // update states
    curr_states.state_B = state_B; // update states
}