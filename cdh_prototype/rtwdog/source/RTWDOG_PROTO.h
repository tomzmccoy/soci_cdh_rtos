#ifndef RTWDOG_PROTO
#define RTWDOG_PROTO

/* Prototypes for functions made below */
void setUpWDOG(void);
void refreshRTWDOGTimer(void);
void resetRTWDOG(void);
void idleTaskRTWDOGRefreshTest(void);
void RTWDOG_IRQ_Handler_Idle(uint8_t idle_flag);




#endif
