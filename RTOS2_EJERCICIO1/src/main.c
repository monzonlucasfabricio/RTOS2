#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "sapi.h"
#include "tareas.h"
#include "debounce.h"


DEBUG_PRINT_ENABLE;

xQueueHandle cola;												//Queue Handle

int main(void) {

	boardConfig();												//Board Init

	cola = xQueueCreate(10, sizeof(void*));						//Create the Queue
	if(cola==NULL){                   							//Check if it was successfully created
		while(1){
			printf("Could not create the queue");
		}
	}

	debugPrintConfigUart( UART_USB, 115200 );					//UART begin

	ButtonConfig[0].Tecla = TEC1;								//Button 1 begin
	ButtonConfig[1].Tecla = TEC2;								//Button 2 begin

	BaseType_t res;

	// Blink led task
	res =xTaskCreate(TareaA,(const char *) "TareaA",configMINIMAL_STACK_SIZE * 2,0,tskIDLE_PRIORITY + 1,0);
	// Button polling task and timing measurement
	res =xTaskCreate(TareaB,(const char *) "TareaB",configMINIMAL_STACK_SIZE * 2,ButtonConfig,tskIDLE_PRIORITY + 1,0);
	// Take message and send to UART
	res =xTaskCreate(TareaC,(const char *) "TareaC",configMINIMAL_STACK_SIZE * 2,0,tskIDLE_PRIORITY + 1,0);

	if (res == pdFAIL) {
		printf("Could not create tasks");
	}

	vTaskStartScheduler();										//Start Scheduler

	while (TRUE) {
	}

	return 0;
}

