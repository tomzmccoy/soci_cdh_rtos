#ifndef RTWDOG_PROTO
#define RTWDOG_PROTO

#include "fsl_debug_console.h" // PRINTF statement
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_rtwdog.h"
#include "idle_task.h"

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
#define RTWDOG_BASE RTWDOG

/* Prototypes for functions made below */
void setUpWDOG(void);
void refreshRTWDOGTimer(void);
void resetRTWDOG(void);
void idleTaskRTWDOGRefreshTest(void);
void RTWDOG_IRQ_Handler_Idle(uint8_t idle_flag);

#define DELAY_TIME 0x12A05F20 // 2.5 seconds on a 125 MHz clock


#endif
