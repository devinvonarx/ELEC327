#include "state_machine_logic.h"
#include <ti/devices/msp/msp.h>
#include <stdint.h>

/* Global state counters */
static uint8_t second_counter = 0;   // 0-11 (the inner ring positions)
static uint8_t position_counter = 0; // 0-143 (the outer ring positions)

static const uint8_t outer_ring_pins[12] = {
    0,   // Position 0  (12 o'clock) - PA0
    26,  // Position 1  (1 o'clock)  - PA26
    24,  // Position 2  (2 o'clock)  - PA24
    22,  // Position 3  (3 o'clock)  - PA22 
    18,  // Position 4  (4 o'clock)  - PA18 
    16,  // Position 5  (5 o'clock)  - PA16 
    14,  // Position 6  (6 o'clock)  - PA14 
    12,  // Position 7  (7 o'clock)  - PA12
    10,  // Position 8  (8 o'clock)  - PA10 
    8,   // Position 9  (9 o'clock)  - PA8 
    6,   // Position 10 (10 o'clock) - PA6 
    28,  // Position 11 (11 o'clock) - PA28
};

static const uint8_t inner_ring_pins[12] = {
    27,  // Position 0  (12 o'clock) - PA27
    25,  // Position 1  (1 o'clock)  - PA25 
    23,  // Position 2  (2 o'clock)  - PA23 
    21,  // Position 3  (3 o'clock)  - PA21 
    17,  // Position 4  (4 o'clock)  - PA17 
    15,  // Position 5  (5 o'clock)  - PA15 
    13,  // Position 6  (6 o'clock)  - PA13 
    11,  // Position 7  (7 o'clock)  - PA11 
    9,   // Position 8  (8 o'clock)  - PA9  
    7,   // Position 9  (9 o'clock)  - PA7 
    5,   // Position 10 (10 o'clock) - PA5 
    1,   // Position 11 (11 o'clock) - PA1 
};

/* advance the clock state */
int GetNextState(int current_state)
{
    /* increase second counter */
    second_counter++;
    if (second_counter >= 12) {
        second_counter = 0;
    }
    
    /* increase minute counter */
    position_counter++;
    if (position_counter >= 144) {
        position_counter = 0;
    }
    
    return current_state;
}

/* generate GPIO output pattern */
int GetStateOutputGPIOA(int current_state)
{
    /* LEDs start off */
    uint32_t output = 0xFFFFFFFF;
    
    /* calculate which outer ring LED should be on */
    uint8_t outer_position = position_counter / 12; 
    uint8_t outer_pin = outer_ring_pins[outer_position];
    output &= ~(1u << outer_pin);  
    
    /* calculate which inner ring LED should be on */
    uint8_t inner_pin = inner_ring_pins[second_counter];
    output &= ~(1u << inner_pin); 
    
    return output;
}

