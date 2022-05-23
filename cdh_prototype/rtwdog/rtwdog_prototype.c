/**
 * RTWDOG prototype currently in progress to function for idle/EPS task
 * Default clock: RTWDOG_CS[CLK] = BUS_CLK
 * RTWDOG must be reset before it times out, otherwise the RTWDOG
 * forcefully resets the MCU
 */
/**
 * Need to make a fastRefreshTest that initializes the RTWDOG with the proper delays.
 * Essentially replicating what was in the example.
 */

/**
 * Need to add constants that will flag when to run the RTWDOG initialization
 * so as not to have it run prematurely and break
 */

/**
 * @file    rtwdog_prototype.c
 * @brief   Application entry point.
 */


#include "RTWDOG_PROTO.h"



static rtwdog_config_t config;


/**
 * Unlock sequence written to CNT register, must be within 16 bus clocks at any time after
 * RTWDOG has been configured
 */
//void setUpWDOG(void) {
//	DisableInterrupts; // disable global interrupt
//	RTWDOG_CNT = UNLOCK_RTWDOG; // unlock the RTWDOG
//	// while (RTWDOG_CS[ULK] == 0); // wait until registers are unlocked              * not too sure what this does?
//	RTWDOG_TOVAL = 256; // Set the timeout value                                   // 40 kHz clock? (TOVAL = 2,400,000 clock ticks)
//	RTWDOG_CS = ENABLE_WATCHDOG; // unlock the RTWDOG with desired configuration
//	// while (WDOG_CS[RCS] == 0); // wait until new configuration takes effect        * not too sure what this does?
//	EnableInterrupts; // re-enable the global interrupt
//}

/**
 * Function that is called to refresh the RTWDOG timer if the task passes down the appropriate flag
 */
//void refreshRTWDOGTimer(void) {
//	DisableInterrupts; // disable global interrupt
//	RTWDOG_CNT = REFRESH_RTWDOG; // refresh the RTWDOG
//	EnableInterrupts; // enable the global interrupt
//}

/**
 * Function to disable/reset the RTWDOG.
 * Resetting the RTWDOG is required if there is need to reconfigure it,
 * if the CS_UPDATE register is low
 */
//void resetRTWDOG(void) {
//	DisableInterrupts; // disable global interrupt
//	RTWDOG_CNT = UNLOCK_RTWDOG; // unlocks the RTWDOG
//	RTWDOG_CS = RESET_RTWDOG; // disable the RTWDOG by turning off WDOG_CS[EN]
//	EnableInterrupts; // enable global interrupt
//}

/**
 * Function to pass down status of idle task. If task completed successfully, refresh the RTWDOG
 * Void function for now, but plan is to pass down a flag from idle task saying it completed successfully,
 * and if it is high, then refresh the WDOG
 */
//void idleTaskRTWDOGRefreshTest(void) {
//	/* pseudo-code for the idle task refresh test */
//
//	/* if (idleTaskSuccessful and timeIsAsExpected) {
//		refreshRTWDOGTimer();
//	} else {
//		// do not really need the else, as the RTWDOG should reset the MCU on its own if not refreshed after threshold time
//	} */
//}

void initializeRTWDOG(void) {
	CLOCK_EnableClock(kCLOCK_Wdog3);
	uint32_t temp;

	/* When system is boot up, WDOG32 is disabled. We must wait for at least 2.5
     * periods of wdog32 clock to reconfigure wodg32. So Delay a while to wait for
     * the previous configuration taking effect. */
    for (temp = 0; temp < DELAY_TIME; temp++)
    {
        __NOP();
    }

    /*
     * config.enableWdog32 = true;
     * config.clockSource = kWDOG32_ClockSource1;
     * config.prescaler = kWDOG32_ClockPrescalerDivide1;
     * config.testMode = kWDOG32_TestModeDisabled;
     * config.enableUpdate = true;
     * config.enableInterrupt = false;
     * config.enableWindowMode = false;
     * config.windowValue = 0U;
     * config.timeoutValue = 0xFFFFU;
     */
    RTWDOG_GetDefaultConfig(&config);
    config.enableInterrupt = false;
    config.clockSource = kRTWDOG_ClockSource1; // change to 32.768 kHz bus clock
    config.timeoutValue = 0x180;     // set the timeout value to 3 secs for 125 MHz bus clock
    config.prescaler    = kRTWDOG_ClockPrescalerDivide256; // prescaler to increase the timeout value

    /* initialize the rtwdog timer */
    RTWDOG_Init(RTWDOG, &config);


    // calling refresh function in the idle_task.
    // 1. what do i need the interrupt handler for and what exactly is it doing by
    // clearing those flags?

    // 2. Do I need all those preprocessor flags or just always initialize it?
}
