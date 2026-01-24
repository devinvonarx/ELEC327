/**
 * state_machine_logic.c
 * 
 * Implements clock logic for LED ring PCB
 * - Outer ring (A LEDs): Hours hand - completes rotation in 144 seconds (12 positions × 12)
 * - Inner ring (B LEDs): Seconds hand - completes rotation in 12 seconds
 * 
 * State updates every second (1Hz)
 * 
 * Inner ring sequence (clockwise from 12 o'clock):
 * D11, D12, D13, D14, D16, D17, D18, D19, D20, D21, D22, D23
 */

#include "state_machine_logic.h"
#include <ti/devices/msp/msp.h>
#include <stdint.h>

/* Global state counters */
static uint8_t second_counter = 0;   // 0-11 (inner ring position, wraps every 12 seconds)
static uint8_t position_counter = 0; // 0-143 (outer ring position, wraps every 144 seconds)

/**
 * Outer ring (A LEDs) - Maps clock position (0-11) to PA pin number
 * Sequence: D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12
 * 
 * From test: PA6=D11, PA14=D7, PA16=D6, PA28=D12
 * Already verified from schematic: PA0, PA8, PA10, PA12, PA18, PA22, PA24, PA26
 */
static const uint8_t outer_ring_pins[12] = {
    0,   // Position 0  (12 o'clock) - PA0  - D1? (was LED12A)
    26,  // Position 1  (1 o'clock)  - PA26 - D2? (was LED1A)
    24,  // Position 2  (2 o'clock)  - PA24 - D3? (was LED2A)
    22,  // Position 3  (3 o'clock)  - PA22 - D4? (was LED3A)
    18,  // Position 4  (4 o'clock)  - PA18 - D5? (was LED4A)
    16,  // Position 5  (5 o'clock)  - PA16 - D6 (VERIFIED from test)
    14,  // Position 6  (6 o'clock)  - PA14 - D7 (VERIFIED from test)
    12,  // Position 7  (7 o'clock)  - PA12 - D8? (was LED7A)
    10,  // Position 8  (8 o'clock)  - PA10 - D9? (was LED8A)
    8,   // Position 9  (9 o'clock)  - PA8  - D10? (was LED9A)
    6,   // Position 10 (10 o'clock) - PA6  - D11 (VERIFIED from test)
    28,  // Position 11 (11 o'clock) - PA28 - D12 (VERIFIED from test)
};

/**
 * Inner ring (B LEDs) - Maps clock position (0-11) to PA pin number
 * Sequence verified: D11, D12, D13, D14, D16, D17, D18, D19, D20, D21, D22, D23
 * 
 * Key corrections:
 * - Position 5: Need PA pin for D17 (was skipping)
 * - Position 7: Need PA pin for D19 (was showing D7)
 * - Position 11: Need PA pin for D23 (was skipping)
 * 
 * From schematic we know:
 * - PA7  = LED9B  (should be D21 based on position 9)
 * - PA9  = LED8B  (should be D20 based on position 8)
 * - PA11 = LED7B  (but this is showing as D7, not D11!)
 * - PA19 = LED4B  (should be D18 based on position 6)
 * - PA21 = LED3B  (should be D16 based on position 4)
 * - PA23 = LED2B  (should be D14 based on position 3)
 * - PA25 = LED1B  (should be D13 based on position 2)
 * - PA27 = LED12B (should be D12 based on position 1)
 */
/**
 * Inner ring (B LEDs) - Maps clock position (0-11) to PA pin number
 * Sequence: D13, D14, (D15?), D16, D17, D18, D19, D20, D21, D22, D23, D24
 * 
 * From find_missing_leds.c results:
 * PA1=D24, PA5=D23, PA7=D22, PA9=D21, PA11=D20, PA13=D19, PA15=D18, PA17=D17
 * PA21=D16, PA25=D14, PA27=D13
 * 
 * Missing: D15 (might not exist, or need to find another pin)
 */
static const uint8_t inner_ring_pins[12] = {
    27,  // Position 0  (12 o'clock) - PA27 - D13 (VERIFIED)
    25,  // Position 1  (1 o'clock)  - PA25 - D14 (VERIFIED)
    23,  // Position 2  (2 o'clock)  - PA23 - D15 (GUESS - trying PA23)
    21,  // Position 3  (3 o'clock)  - PA21 - D16 (VERIFIED)
    17,  // Position 4  (4 o'clock)  - PA17 - D17 (VERIFIED)
    15,  // Position 5  (5 o'clock)  - PA15 - D18 (VERIFIED)
    13,  // Position 6  (6 o'clock)  - PA13 - D19 (VERIFIED)
    11,  // Position 7  (7 o'clock)  - PA11 - D20 (VERIFIED)
    9,   // Position 8  (8 o'clock)  - PA9  - D21 (VERIFIED)
    7,   // Position 9  (9 o'clock)  - PA7  - D22 (VERIFIED)
    5,   // Position 10 (10 o'clock) - PA5  - D23 (VERIFIED)
    1,   // Position 11 (11 o'clock) - PA1  - D24 (VERIFIED)
};

/**
 * GetNextState - Advance the clock state by one second
 */
int GetNextState(int current_state)
{
    /* Increment second counter (inner ring) */
    second_counter++;
    if (second_counter >= 12) {
        second_counter = 0;
    }
    
    /* Increment position counter (outer ring) */
    position_counter++;
    if (position_counter >= 144) {
        position_counter = 0;
    }
    
    return current_state;
}

/**
 * GetStateOutputGPIOA - Generate GPIO output pattern for both LED rings
 */
int GetStateOutputGPIOA(int current_state)
{
    /* Start with all LEDs OFF (all bits HIGH for active-low) */
    uint32_t output = 0xFFFFFFFF;
    
    /* Calculate which outer ring LED should be ON */
    uint8_t outer_position = position_counter / 12;  // Maps 0-143 to 0-11
    uint8_t outer_pin = outer_ring_pins[outer_position];
    output &= ~(1u << outer_pin);  // Clear bit to turn LED ON
    
    /* Calculate which inner ring LED should be ON */
    uint8_t inner_pin = inner_ring_pins[second_counter];
    output &= ~(1u << inner_pin);  // Clear bit to turn LED ON
    
    return output;
}

/**
 * GetStateOutputGPIOB - Not used, all LEDs on GPIOA
 */
int GetStateOutputGPIOB(int current_state)
{
    return 0xFFFFFFFF;
}