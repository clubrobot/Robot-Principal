//
// Created by bapti on 04/11/2024.
//

/**
 *  @file variables_globales.h
 *  @ingroup core
 */

#ifndef TEAM2025_VARIABLES_GLOBALES_H
#define TEAM2025_VARIABLES_GLOBALES_H
#include "FreeRTOS.h"
#include "FreeRTOS/Source/include/task.h"

/**@{
 *@ingroup globals
 */
//TODO: (2026-06-25) utiliser un enum au lieu de bool
#define TEAM_BLEU 0
#define TEAM_JAUNE 1
/// Quel team sommes-nous
extern bool my_team;
/// Est-ce que le match a débuté
extern bool match_started;
///@}
/** @defgroup taskhandles
  * @ingroup globals
  * Handle de toutes les tâches
  * @{
  */
/// Handle de la tâche de stratégie
inline TaskHandle_t hl_robot;
/// Handle de la tâche de base roulante
inline TaskHandle_t hl_wb;
/// Handle de la tâche des sensors
inline TaskHandle_t hl_sens;
/// Handle de la tâche du préhenseur
inline TaskHandle_t  gripper_handle;
/// Handle de lt tâche du killer
inline TaskHandle_t  killer_handle;
///@}
#endif //TEAM2025_VARIABLES_GLOBALES_H
