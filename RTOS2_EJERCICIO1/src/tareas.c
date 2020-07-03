#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "sapi.h"
#include <string.h>
#include "task.h"
#include "debounce.h"
#include "tareas.h"

extern xQueueHandle cola;

void TareaA(void* pvParameter) {

	portTickType xPeriodicity = 1000/ portTICK_PERIOD_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();
	char msg[] = "LED ON";
	char *pointer = NULL;

	while (TRUE) {

		gpioToggle( LED1 );
		taskENTER_CRITICAL ( );
		pointer = pvPortMalloc(LEDON);
		taskEXIT_CRITICAL ( );
		if(pointer != NULL){
			memcpy(pointer,msg, LEDON);
			xQueueSend(cola, (void *) &pointer, portMAX_DELAY);
		}
		vTaskDelayUntil(&xLastWakeTime, xPeriodicity);
	}
}


void TareaB(void* pvParameter) {

	Button_t* config = (Button_t*) pvParameter;
	for (uint8_t i = 0; i < CANT_TECLAS; i++){										//Button Init
		FsmButtonInit(&config[i]);
	}
	portTickType xPeriodicity =  40/portTICK_PERIOD_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();

	uint8_t j = 0;

	while(TRUE) {

		for (j = 0; j < CANT_TECLAS; j++){
			FsmButtonControl(&config[j]);											//Button control
			vTaskDelayUntil( &xLastWakeTime, xPeriodicity );
		}
	}
}


void TareaC(void* pvParameter) {
	char *msg = NULL;

	while(TRUE) {

		if(xQueueReceive(cola, &msg, portMAX_DELAY) == pdTRUE){
		printf("%s\r\n", msg);
		}

		taskENTER_CRITICAL ( );
		vPortFree(msg);
		taskEXIT_CRITICAL ( );

   }
	vTaskDelete(NULL);
}
