#ifndef INITIALIZE_LEDS_H
#define INITIALIZE_LEDS_H

#include <stdint.h>

/* Public function */
void InitializeGPIO(void);

/* ---- Shared LED bit masks on GPIOA ---- */
#define GPIO_FUNC1          (0x00000001u)
#define PA_BIT(n)           (1u << (n))

/* Outer ring (A) */
#define LED12A  PA_BIT(0)
#define LED11A  PA_BIT(28)
#define LED10A  PA_BIT(6)
#define LED9A   PA_BIT(8)
#define LED8A   PA_BIT(10)
#define LED7A   PA_BIT(15)
#define LED6A   PA_BIT(14)
#define LED5A   PA_BIT(13)
#define LED4A   PA_BIT(12)
#define LED3A   PA_BIT(22)
#define LED2A   PA_BIT(24)
#define LED1A   PA_BIT(26)

/* Inner ring (B) */
#define LED12B  PA_BIT(27)
#define LED11B  PA_BIT(1)
#define LED10B  PA_BIT(5)
#define LED9B   PA_BIT(7)
#define LED8B   PA_BIT(9)
#define LED7B   PA_BIT(11)
#define LED6B   PA_BIT(16)
#define LED5B   PA_BIT(17)
#define LED4B   PA_BIT(18)
#define LED3B   PA_BIT(21)
#define LED2B   PA_BIT(23)
#define LED1B   PA_BIT(25)

/* All LED pins on GPIOA */
#define ALL_LED_BITS_A ( \
    LED12A | LED11A | LED10A | LED9A | LED8A | LED7A | LED6A | LED5A | \
    LED4A  | LED3A  | LED2A  | LED1A  | \
    LED12B | LED11B | LED10B | LED9B | LED8B | LED7B | LED6B | LED5B | \
    LED4B  | LED3B  | LED2B  | LED1B \
)

#endif
