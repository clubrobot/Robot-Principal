//
// Created by bapti on 04/11/2024.
//

#ifndef TEAM2025_VARIABLES_GLOBALES_H
#define TEAM2025_VARIABLES_GLOBALES_H
#include "FreeRTOS.h"
#include "FreeRTOS/Source/include/task.h"

#define TEAM_BLEU 0
#define TEAM_JAUNE 1
extern bool my_team;
extern bool match_started;
inline TaskHandle_t hl_robot;
#endif //TEAM2025_VARIABLES_GLOBALES_H
