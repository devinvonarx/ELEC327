#include "initialize_leds.h"
#include "delay.h"
#include <ti/devices/msp/msp.h>
#include <stdint.h>

#define POWER_STARTUP_DELAY (16u)

/* Configure a PINCM entry for GPIO function and "connected" */
static inline void mux_gpio(uint32_t pincm_const)
{
    IOMUX->SECCFG.PINCM[pincm_const] = (IOMUX_PINCM_PC_CONNECTED | 0x1u);
}

void InitializeGPIO(void)
{
    /* 1) Reset + power GPIOA */
    GPIOA->GPRCM.RSTCTL =
        GPIO_RSTCTL_KEY_UNLOCK_W |
        GPIO_RSTCTL_RESETSTKYCLR_CLR |
        GPIO_RSTCTL_RESETASSERT_ASSERT;

    GPIOA->GPRCM.PWREN =
        GPIO_PWREN_KEY_UNLOCK_W |
        GPIO_PWREN_ENABLE_ENABLE;

    delay_cycles(POWER_STARTUP_DELAY);

    /* 2) IOMUX configuration - CORRECTED mappings from Table 6-2 */
    mux_gpio(IOMUX_PINCM1);   /* PA0  - LED12A */
    mux_gpio(IOMUX_PINCM2);   /* PA1  */
    mux_gpio(IOMUX_PINCM7);   /* PA2  */
    mux_gpio(IOMUX_PINCM10);  /* PA5  */
    mux_gpio(IOMUX_PINCM11);  /* PA6  */
    mux_gpio(IOMUX_PINCM14);  /* PA7  - LED9B */
    mux_gpio(IOMUX_PINCM19);  /* PA8  - LED9A */
    mux_gpio(IOMUX_PINCM20);  /* PA9  - LED8B */
    mux_gpio(IOMUX_PINCM21);  /* PA10 - LED8A */
    mux_gpio(IOMUX_PINCM22);  /* PA11 - LED7B */
    mux_gpio(IOMUX_PINCM34);  /* PA12 - LED7A */
    mux_gpio(IOMUX_PINCM35);  /* PA13 */
    mux_gpio(IOMUX_PINCM36);  /* PA14 */
    mux_gpio(IOMUX_PINCM37);  /* PA15 */
    mux_gpio(IOMUX_PINCM38);  /* PA16 */
    mux_gpio(IOMUX_PINCM39);  /* PA17 */
    mux_gpio(IOMUX_PINCM40);  /* PA18 - LED4A */
    mux_gpio(IOMUX_PINCM46);  /* PA21 - LED3B */
    mux_gpio(IOMUX_PINCM47);  /* PA22 - LED3A */
    mux_gpio(IOMUX_PINCM53);  /* PA23 - LED2B */
    mux_gpio(IOMUX_PINCM54);  /* PA24 - LED2A */
    mux_gpio(IOMUX_PINCM55);  /* PA25 - LED1B */
    mux_gpio(IOMUX_PINCM59);  /* PA26 - LED1A */
    mux_gpio(IOMUX_PINCM60);  /* PA27 - LED12B */
    mux_gpio(IOMUX_PINCM3);   /* PA28 */

    /* 3) Set all LEDs to OFF (HIGH for active-low) and enable outputs */
    uint32_t leds = (1u<<0)  | (1u<<1)  | (1u<<2)  |
                    (1u<<5)  | (1u<<6)  | (1u<<7)  | (1u<<8)  |
                    (1u<<9)  | (1u<<10) | (1u<<11) | (1u<<12) |
                    (1u<<13) | (1u<<14) | (1u<<15) | (1u<<16) |
                    (1u<<17) | (1u<<18) |
                    (1u<<21) | (1u<<22) | (1u<<23) | (1u<<24) |
                    (1u<<25) | (1u<<26) | (1u<<27) | (1u<<28);

    GPIOA->DOUTSET31_0 = leds; // OFF (active-low)
    GPIOA->DOESET31_0 = leds;  // enable outputs
}