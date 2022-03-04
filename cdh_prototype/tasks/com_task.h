/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "clock_config.h"

/*******************************************************************************
 * Function declarations
 ******************************************************************************/
extern TaskHandle_t TaskHandler_img;

void com_task(void *pvParameters);
void initialization_PIT(void);
