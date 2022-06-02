/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

/* Freescale includes. */
//#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_common.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
//#include "fsl_gpio.h"

/* Peripherals includes. */
//#include "fsl_lpuart_freertos.h"
//#include "fsl_lpuart.h"
#include "peripherals.h"

/* Tasks includes.*/
#include "idle_task.h"
#include "imag_task.h"
#include "gnc_task.h"
#include "com_task.h"

/* Standard libraries includes.*/
//#include "semphr.h"
#include <stdbool.h>
//#include "semc_sdram.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define CPU_NAME "iMXRT1021"

/* Task priorities. */
#define idle_task_PRIORITY	 			2
#define imag_task_PRIORITY 				2
#define com_task_PRIORITY				2
#define gnc_task_PRIORITY 				2
#define max_PRIORITY 	   				(configMAX_PRIORITIES - 1)


/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Application entry point.
 */

//#define EXAMPLE_LED_GPIO     BOARD_USER_LED_GPIO
//#define EXAMPLE_LED_GPIO_PIN BOARD_USER_LED_GPIO_PIN
//
///* The PIN status */
//volatile bool g_pinSet = false;

//mTask handlers declared in each task files in tasks folder.
extern TaskHandle_t TaskHandler_idle;
extern TaskHandle_t TaskHandler_com;
extern TaskHandle_t TaskHandler_img;

/*!
 * @brief main demo function.
 */
int main(void)
{

	/* Init board hardware. */
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();
    BOARD_InitPeripherals();

    initializeRTWDOG();
//    /* Define the init structure for the output LED pin*/
//    gpio_pin_config_t led_config = {kGPIO_DigitalOutput, 0, kGPIO_NoIntmode};
//    /* Print a note to terminal. */
//	PRINTF("\r\n GPIO Driver example\r\n");
//	PRINTF("\r\n The LED is blinking.\r\n");
//
//	/* Init output LED GPIO. */
//	GPIO_PinInit(EXAMPLE_LED_GPIO, EXAMPLE_LED_GPIO_PIN, &led_config);
//
//	while (1)
//	{
//		SDK_DelayAtLeastUs(100000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
//#if (defined(FSL_FEATURE_IGPIO_HAS_DR_TOGGLE) && (FSL_FEATURE_IGPIO_HAS_DR_TOGGLE == 1))
//		GPIO_PortToggle(EXAMPLE_LED_GPIO, 1u << EXAMPLE_LED_GPIO_PIN);
//#else
//		if (g_pinSet)
//		{
//			GPIO_PinWrite(EXAMPLE_LED_GPIO, EXAMPLE_LED_GPIO_PIN, 0U);
//			g_pinSet = false;
//		}
//		else
//		{
//			GPIO_PinWrite(EXAMPLE_LED_GPIO, EXAMPLE_LED_GPIO_PIN, 1U);
//			g_pinSet = true;
//		}
//#endif /* FSL_FEATURE_IGPIO_HAS_DR_TOGGLE */
//	}



    if (xTaskCreate(idle_task, "idle_task", configMINIMAL_STACK_SIZE + 100, NULL, max_PRIORITY , &TaskHandler_idle) != //initialize priority to the highest +1
        pdPASS)
    {
        PRINTF("Task creation failed!.\r\n");
        while (1)
            ;
    }
   if (xTaskCreate(imag_task, "imag_task", configMINIMAL_STACK_SIZE + 100, NULL, imag_task_PRIORITY, &TaskHandler_img) !=
		   pdPASS)
	 {
        PRINTF("Task creation failed!.\r\n");
        while (1)
          ;
	 }
   if (xTaskCreate(com_task, "com_task", configMINIMAL_STACK_SIZE + 100, NULL, com_task_PRIORITY, &TaskHandler_com) !=
	 	    pdPASS)
	 {
        PRINTF("Task creation failed!.\r\n");
        while (1)
          ;
	 }
   if (xTaskCreate(gnc_task, "gnc_task", configMINIMAL_STACK_SIZE + 100, NULL, gnc_task_PRIORITY, NULL) !=
		    pdPASS)
	 {
        PRINTF("Task creation failed!.\r\n");
        while (1)
          ;
	 }
    vTaskStartScheduler();
    for (;;)
        ;
}
