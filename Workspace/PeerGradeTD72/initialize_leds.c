#include "initialize_leds.h"
#include "delay.h"
#include <ti/devices/msp/msp.h>

#define POWER_STARTUP_DELAY (16)

void InitializeGPIO() {
    // 1. Reset GPIO port (the one(s) for pins that you will use)
    GPIOA->GPRCM.RSTCTL = (GPIO_RSTCTL_KEY_UNLOCK_W | GPIO_RSTCTL_RESETSTKYCLR_CLR | GPIO_RSTCTL_RESETASSERT_ASSERT);

    // 2. Enable power on LED GPIO port
    GPIOA->GPRCM.PWREN = (GPIO_PWREN_KEY_UNLOCK_W | GPIO_PWREN_ENABLE_ENABLE);

    delay_cycles(POWER_STARTUP_DELAY); // delay to enable GPIO to turn on and reset

    /*
 * Each IOMUX->PINCM register controls ONE physical pin.
 * 
 * - IOMUX_PINCM_PC_CONNECTED connects the pad to the SoC
 * - Function value 0x1 selects GPIO mode
 *
 * Without this step, GPIO writes would toggle internal logic
 * but never reach the physical LED pin.
 */

    // initialize the hours pins
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM1)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //LED12A
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM59)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //LED1A
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM54)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //LED2A
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM47)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //LED3A
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM40)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //LED4A
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM38)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //LED5A
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM36)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //LED6A
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM34)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //LED7A
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM21)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //LED8A
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM19)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //LED9A
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM11)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //LED10A
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM3)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //LED11A

    // initialize the minutes pins
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM60)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //LED12B
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM55)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //LED1B
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM53)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //LED2B
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM46)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //LED3B
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM39)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //LED4B
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM37)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //LED5B
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM35)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //LED6B
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM22)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //LED7B
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM20)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //LED8B
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM14)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //LED9B
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM10)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //LED10B
    IOMUX->SECCFG.PINCM[(IOMUX_PINCM2)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001)); //LED11B

 /*
 * Initialize all LED pins to HIGH.
 *
 * The PCB LEDs are wired active-low:
 *   GPIO HIGH  -> LED OFF
 *   GPIO LOW   -> LED ON
 *
 * Writing to DOUTSET31_0 drives selected pins HIGH without
 * affecting other GPIOA pins.
 * GPIOA contains 32 GPIO pins labeled PA0 through PA31.
 * Each bit in a 32-bit GPIO register corresponds to exactly ONE GPIO pin:
 *
 *   bit 0  → PA0
 *   bit 1  → PA1
 *   ...
 *   bit 31 → PA31
 *
 * This PCB uses ONLY 24 of those pins to drive LEDs
 *
 * The hexadecimal value below is a BITMASK:
 *   - A bit value of '1' means "this GPIO pin is connected to an LED"
 *   - A bit value of '0' means "this GPIO pin is unused"
 * The same mask is used for:
 *   - DOESET31_0 : enabling output drivers only on LED pins
 *   - DOUTSET31_0: initializing all LED pins HIGH (LEDs OFF, active-low)
 */
    GPIOA->DOESET31_0 = (0x1FE7FFE3);
    GPIOA->DOUTSET31_0 = (0x1FE7FFE3);
}
