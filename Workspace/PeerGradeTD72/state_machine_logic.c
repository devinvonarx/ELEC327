#include "state_machine_logic.h"
#include "initialize_leds.h"  /* LED_ALL_MASK */

/* Index convention: 0=12 o'clock, 1=1 o'clock, ..., 11=11 o'clock */

/* Outer ring (Hours): LED12A..LED11A */
static const uint32_t outer_bits[12] = {
    (1u << 0),   /* idx0  LED12A PA0  */
    (1u << 26),  /* idx1  LED1A  PA26 */
    (1u << 24),  /* idx2  LED2A  PA24 */
    (1u << 22),  /* idx3  LED3A  PA22 */
    (1u << 18),  /* idx4  LED4A  PA18 */
    (1u << 16),  /* idx5  LED5A  PA16 */
    (1u << 14),  /* idx6  LED6A  PA14 */
    (1u << 12),  /* idx7  LED7A  PA12 */
    (1u << 10),  /* idx8  LED8A  PA10 */
    (1u << 8),   /* idx9  LED9A  PA8  */
    (1u << 6),   /* idx10 LED10A PA6  */
    (1u << 28)   /* idx11 LED11A PA28 */
};

/* Inner ring (Minutes/Seconds): LED12B..LED11B */
static const uint32_t inner_bits[12] = {
    (1u << 27),  /* idx0  LED12B PA27 */
    (1u << 25),  /* idx1  LED1B  PA25 */
    (1u << 23),  /* idx2  LED2B  PA23 */
    (1u << 21),  /* idx3  LED3B  PA21 */
    (1u << 17),  /* idx4  LED4B  PA17 */
    (1u << 15),  /* idx5  LED5B  PA15 */
    (1u << 13),  /* idx6  LED6B  PA13 */
    (1u << 11),  /* idx7  LED7B  PA11 */
    (1u << 9),   /* idx8  LED8B  PA9  */
    (1u << 7),   /* idx9  LED9B  PA7  */
    (1u << 5),   /* idx10 LED10B PA5  */
    (1u << 1)    /* idx11 LED11B PA1  */
};

ClockState Clock_Init(void)
{
    ClockState s;
    s.inner_idx = 0u; /* 12 o'clock */
    s.outer_idx = 0u; /* 12 o'clock */
    s.tick      = 0u;
    return s;
}

ClockState Clock_Next(ClockState s)
{
    /* Called once per second */
    s.tick++;

    /* Inner ring advances every second */
    s.inner_idx = (s.inner_idx + 1u) % 12u;

    /* Outer ring advances every 12 seconds */
    if ((s.tick % 12u) == 0u) {
        s.outer_idx = (s.outer_idx + 1u) % 12u;
    }

    return s;
}

uint32_t Clock_OnMaskGPIOA(ClockState s)
{
    uint32_t mask = outer_bits[s.outer_idx] | inner_bits[s.inner_idx];

    /* This code ensure mask only contains LED pins */
    mask &= LED_ALL_MASK;

    return mask;
}
