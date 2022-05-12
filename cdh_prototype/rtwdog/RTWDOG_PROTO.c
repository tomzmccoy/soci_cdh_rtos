/**
 * RTWDOG prototype currently in progress to function for idle/EPS task
 * Default clock: RTWDOG_CS[CLK] = BUS_CLK
 */

/**
 * @file    RTWDOG_PROTO.c
 * @brief   Application entry point.
 */
#include "fsl_debug_console.h" // PRINTF statement
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_rtwdog.h"

/**
 * All of my personal defines here that I need. This is for RTWDOG refresh, RTWDOG config, etc.
 */
#define UNLOCK_RTWDOG (0xD928C520) // unlock sequence to be written to CNT register

/**
 * WDOG define that is non configurable unless there is a reset.
 * Window mode is off (subject to change), enable is on, interrupts are on, update is off, clk is BUS_CLK
 */
#define ENABLE_WATCHDOG (WDOG_CS_EN(1) | WDOG_CS_CLK(0) | WDOG_CS_INT(1) | WDOG_CS_WIN(0) | WDOG_CS_UPDATE(0))

/* Mask to reset the RTWDOG. Must set it equal to WDOG_CS to reset the RTWDOG */
#define RESET_RTWDOG (WDOG_CS & ~WDOG_CS_EN_MASK)

/**
 * Value to refresh the RTWDOG written to the CNT register.
 * Written as one 32-bit write instead of two 16-bit writes.
 * The refresh sequence must occur before the WDG timeout;
 * otherwise, the RTWDOG resets the MCU
 */
#define REFRESH_RTWDOG 0xB480A602

/* Prototypes for functions made below */
void setUpWDOG(void);
void refreshRTWDOGTimer(void);
void resetRTWDOG(void);
void idleTaskRTWDOGRefreshTest(void);

/**
 * Unlock sequence written to CNT register, must be within 16 bus clocks at any time after
 * RTWDOG has been configured
 */

void setUpWDOG(void) {
	DisableInterrupts; // disable global interrupt
	RTWDOG_CNT = UNLOCK_RTWDOG; // unlock the RTWDOG
	// while (RTWDOG_CS[ULK] == 0); // wait until registers are unlocked
	WDOG_TOVAL = 256; // Set the timeout value
	WDOG_CS = ENABLE_WATCHDOG;
	// while (WDOG_CS[RCS] == 0); // wait until new configuration takes effect
	EnableInterrupts; // re-enable the global interrupt
}

/**
 * Function that is called to refresh the watchdog timer if the task passes down the appropriate flag
 */
void refreshRTWDOGTimer(void) {
	DisableInterrupts; // disable global interrupt
	WDOG_CNT = REFRESH_RTWDOG; // refresh the RTWDOG
	EnableInterrupts; // enable the global interrupt
}

/**
 * Function to disable/reset the RTWDOG
 */
void resetRTWDOG(void) {
	DisableInterrupts; // disable global interrupt
	WDOG_CNT = UNLOCK_RTWDOG; // unlocks the RTWDOG
	WDOG_CS = RESET_RTWDOG; // disable the watchdog by unsetting the WDOG_CS[EN]
	EnableInterrupts; // enable global interrupt
}
/**
 * Function to pass down status of GNC task. If task completed successfully, refresh the RTWDOG
 * Void function for now, but plan is to pass down a flag from idle task saying it completed successfully,
 * and if it is high, then refresh the WDOG
 */
void idleTaskRTWDOGRefreshTest(void) {
	/* pseudo-code for the idle task refresh test */
	if (idleTaskSuccessful and timeIsAsExpected) {
		refreshRTWDOGTimer();
	} else {
		// do not really need the else, as the RTWDOG should reset the MCU on its own if not refreshed after threshold time
	}
}





/*
 * @brief   Application entry point.
 */
int main(void) {

    /* Init board hardware. */
    BOARD_ConfigMPU();
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    PRINTF("Hello World\n");

    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++ ;
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
    return 0 ;
}
