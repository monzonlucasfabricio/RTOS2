#ifndef MIS_PROYECTOS_RTOS2_RTOS2_EJERCICIO1_INC_TAREAS_H_
#define MIS_PROYECTOS_RTOS2_RTOS2_EJERCICIO1_INC_TAREAS_H_

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "sapi.h"


#define LEDON    7

void TareaA(void* pvParameter);
void TareaB(void* pvParameter);
void TareaC(void* pvParameter);


#endif /* MIS_PROYECTOS_RTOS2_RTOS2_EJERCICIO1_INC_TAREAS_H_ */
