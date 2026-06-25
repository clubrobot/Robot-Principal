/**
 * @file wb_thread.h
 * @ingroup wheeledbase
 * @ingroup core
 * @brief Contient les fonctions et variables nécessaires pour gérer le thread de base roulante
 */

#ifndef WB_THREAD_H
#define WB_THREAD_H

#include "wb_const.h"

#include "WheelMotor.h"
#include "Codewheel.h"
#include "Odometry.h"
#include "PID.h"
#include "VelocityController.h"
#include "PositionController.h"
#include "PurePursuit.h"
#include "TurnOnTheSpot.h"

#include "mathutils.h"

// Load the different modules
/**
 * @defgroup wb-componants Composants de la base roulante
 * @ingroup globals
 * @brief Les divers constituants (moteurs, pid...) de la base roulante
 * @{
 */
extern DRV8844 driver;
extern WheelMotor leftWheel;
extern WheelMotor rightWheel;

extern TIM_HandleTypeDef htim23;//Right
extern TIM_HandleTypeDef htim24;//Left

extern Codewheel leftCodewheel;
extern Codewheel rightCodewheel;

extern Odometry odometry;

extern VelocityController velocityControl;
#if ENABLE_VELOCITYCONTROLLER_LOGS
extern VelocityControllerLogs controllerLogs;
#endif // ENABLE_VELOCITYCONTROLLER_LOGS

extern PID linVelPID;
extern PID angVelPID;

extern PositionController positionControl;

extern PurePursuit purePursuit;
extern TurnOnTheSpot turnOnTheSpot;
/// @}

void wb_setup();
void wb_loop(void *pvParameters);

#endif //WB_THREAD_H
