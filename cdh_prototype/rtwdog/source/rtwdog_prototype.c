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

#include "RTWDOG_PROTO.h"
/* Include header files from the tasks to send flags to the RTWDOG timer */
#include "idle_task.h"
//#include "gnc_task.h"
//#include "com_task.h"
//#include "imag_task.h"

/**
 * All of my personal defines here that I need. This is for RTWDOG refresh, RTWDOG config, etc.
 */
#define UNLOCK_RTWDOG (0xD928C520) // unlock sequence to be written to CNT register

/**
 * WDOG define that is non configurable unless there is a reset.
 * Window mode is off (subject to change), enable is on, interrupts are on, update is off, clk is BUS_CLK
 */
#define ENABLE_WATCHDOG (RTWDOG_CS_EN(1) | RTWDOG_CS_CLK(0) | RTWDOG_CS_INT(1) | RTWDOG_CS_WIN(0) | RTWDOG_CS_UPDATE(0))

/* Mask to reset the RTWDOG. Must set it equal to WDOG_CS to reset the RTWDOG */
#define RESET_RTWDOG (RTWDOG_CS & ~RTWDOG_CS_EN_MASK)

/**
 * Value to refresh the RTWDOG written to the CNT register.
 * Written as one 32-bit write instead of two 16-bit writes.
 * The refresh sequence must occur before the WDG timeout;
 * otherwise, the RTWDOG resets the MCU
 */
#define REFRESH_RTWDOG 0xB480A602



/**
 * Function that monitors the refresh of the watchdog. Refreshes if the idle_flag is received as expected
 * If the RTWDOG is not refreshed by the time the countdown timer ends, then it resets the MCU
 */
void RTWDOG_IRQ_Handler_Idle(uint8_t idle_successful) {
	if (idle_successful) {
		refreshRTWDOGTimer();
	}
	idle_flag = 0; // reset the idle flag.
}


/**
 * Unlock sequence written to CNT register, must be within 16 bus clocks at any time after
 * RTWDOG has been configured
 */
void setUpWDOG(void) {
	DisableInterrupts; // disable global interrupt
	RTWDOG_CNT = UNLOCK_RTWDOG; // unlock the RTWDOG
	// while (RTWDOG_CS[ULK] == 0); // wait until registers are unlocked              * not too sure what this does?
	RTWDOG_TOVAL = 256; // Set the timeout value                                      * Need to change to be what the team wants/needs. I do not know how fast this clock is, most likely bad value
	RTWDOG_CS = ENABLE_WATCHDOG; // unlock the RTWDOG with desired configuration
	// while (WDOG_CS[RCS] == 0); // wait until new configuration takes effect        * not too sure what this does?
	EnableInterrupts; // re-enable the global interrupt
}

/**
 * Function that is called to refresh the RTWDOG timer if the task passes down the appropriate flag
 */
void refreshRTWDOGTimer(void) {
	DisableInterrupts; // disable global interrupt
	RTWDOG_CNT = REFRESH_RTWDOG; // refresh the RTWDOG
	EnableInterrupts; // enable the global interrupt
}

/**
 * Function to disable/reset the RTWDOG.
 * Resetting the RTWDOG is required if there is need to reconfigure it,
 * if the CS_UPDATE register is low
 */
void resetRTWDOG(void) {
	DisableInterrupts; // disable global interrupt
	RTWDOG_CNT = UNLOCK_RTWDOG; // unlocks the RTWDOG
	RTWDOG_CS = RESET_RTWDOG; // disable the RTWDOG by turning off WDOG_CS[EN]
	EnableInterrupts; // enable global interrupt
}

/**
 * Function to pass down status of idle task. If task completed successfully, refresh the RTWDOG
 * Void function for now, but plan is to pass down a flag from idle task saying it completed successfully,
 * and if it is high, then refresh the WDOG
 */
void idleTaskRTWDOGRefreshTest(void) {
	/* pseudo-code for the idle task refresh test */

	/* if (idleTaskSuccessful and timeIsAsExpected) {
		refreshRTWDOGTimer();
	} else {
		// do not really need the else, as the RTWDOG should reset the MCU on its own if not refreshed after threshold time
	} */
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

#if // need some sort of check here that says when to check the idle_flag. Because if constantly being checked, could cause unnecessary MCU reset
    RTWDOG_IRQ_Handler_Idle(idle_flag);
#endif
    return 0 ;
}
