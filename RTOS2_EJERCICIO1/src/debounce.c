#include "debounce.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "sapi.h"
#include <string.h>

extern xQueueHandle cola;


void Buttonpressed(Button_t* config){
	config -> down_time = xTaskGetTickCount();

}

void Buttonreleased(Button_t* config ){

	char msg[] = "TECx Tyyyy\r\n";

	char *pointer = NULL;

	config -> up_time = xTaskGetTickCount();

	config -> diff_time = (config -> up_time)-(config -> down_time); 	// Difference time between up_time and down_time

	sprintf(msg,"TECx T%04d\r\n",config -> diff_time);					// Config the time part of the string

	if(config -> Tecla == TEC1){										// Config the button part of the string
		msg[3] = '1';
	}
	else{
		msg[3] = '2';
	}

	taskENTER_CRITICAL ();												// Enter critical section
	pointer = pvPortMalloc(MSG_SIZE);									// Allocate memory
	taskEXIT_CRITICAL ();												// Exit critical section

	if (pointer != NULL){
		memcpy(pointer,msg, MSG_SIZE);
		xQueueSend(cola, (void *) &pointer, portMAX_DELAY);				// Send message to Queue
	}
}

void FsmButtonInit(Button_t* config) {
	config->fallingcount = 0;
	config->risingcount = 0;
	config->Buttonstate=UP_1;
}

void FsmButtonControl(Button_t* config){
	switch (config -> Buttonstate){
	case UP_1:

		if (!gpioRead(config->Tecla)){
			config->Buttonstate = FALLING_1;
		}
		break;

	case FALLING_1 :
		if (config -> fallingcount <= DEBOUNCE_TIME){
			if (!gpioRead(config -> Tecla)){
				config -> Buttonstate = DOWN_1;
				Buttonpressed(config);
			}
			else{
				config -> Buttonstate = UP_1;
			}
			config -> fallingcount = 0;
		}
		config -> fallingcount++;
		break;

	case DOWN_1 :
		if (gpioRead(config -> Tecla)){
			config -> Buttonstate = RISING_1;
		}
		break;

	case RISING_1:
		if (config -> risingcount <= DEBOUNCE_TIME){
			if (gpioRead(config -> Tecla)){
				config -> Buttonstate = UP_1;
				Buttonreleased(config);
			}
			else{
				config -> Buttonstate = DOWN_1;
			}
			config -> risingcount = 0;
		}
		config -> risingcount++;
		break;

	}
}
