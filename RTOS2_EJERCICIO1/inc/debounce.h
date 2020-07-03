#ifndef MIS_PROYECTOS_RTOS2_RTOS2_EJERCICIO1_INC_DEBOUNCE_H_
#define MIS_PROYECTOS_RTOS2_RTOS2_EJERCICIO1_INC_DEBOUNCE_H_

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "sapi.h"
#include "semphr.h"


#ifdef __cplusplus
extern "C" {
#endif

#define CANT_TECLAS			2							//	Button quantity
#define MSG_SIZE			10       					//	Bytes to send
#define DEBOUNCE_TIME		40							//	Debounce time 40 milliseconds

typedef enum {
	UP_1,
	RISING_1,
	DOWN_1,
	FALLING_1,
} Fsm_state_t;

typedef struct
{
	gpioMap_t Tecla;
	Fsm_state_t Buttonstate;
	TickType_t down_time;
	TickType_t up_time;
	TickType_t  diff_time;
	uint8_t fallingcount;
	uint8_t risingcount;

} Button_t;

Button_t  ButtonConfig[CANT_TECLAS];

void Buttonpressed(Button_t* config);
void Buttonreleased(Button_t* config);
void FsmButtonControl(Button_t* config);
void FsmButtonInit(Button_t* config);

#ifdef __cplusplus
}
#endif


#endif /* MIS_PROYECTOS_RTOS2_RTOS2_EJERCICIO1_INC_DEBOUNCE_H_ */
