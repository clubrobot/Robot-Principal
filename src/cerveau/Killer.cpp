//
// Created by Romain Pouvreau on 14/05/2026.
//

#include <FreeRTOS.h>
#include "Killer.h"

#include <cstdio>

#include "Elevator.h"
#include "HazelnutGripper.h"
#include "Wheeledbase.h"
#include "FreeRTOS/Source/include/task.h"

#include "variables_globales.h"
#include "ihm/ihm.h"

void killer::killer_loop(void *pvParameters)
{

    printf("Waiiiting\n");
    vTaskDelay(pdMS_TO_TICKS(100000));

    printf("In comming\n");
    vTaskDelete(gripper_handle);
    vTaskDelete(hl_robot);
    vTaskDelete(hl_wb);
    vTaskDelete(hl_sens);

    leftWheel.setVelocity(0);
    rightWheel.setVelocity(0);

    ihm::ihmLogger.log(SCREEN_LEVEL, "END");

    vTaskDelete(NULL);


}
