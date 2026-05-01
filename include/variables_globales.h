//
// Created by bapti on 04/11/2024.
//

#ifndef TEAM2025_VARIABLES_GLOBALES_H
#define TEAM2025_VARIABLES_GLOBALES_H

#include "cerveau/Automate.h"
#include "FreeRTOS/Source/include/task.h"
#define TEAM_BLEU 0
#define TEAM_JAUNE 1
inline Automate::teamColor my_team = {};
inline bool match_started = {};

inline TaskHandle_t hl_sens = nullptr;
inline TaskHandle_t hl_wb = nullptr;
inline TaskHandle_t hl_robot = nullptr;
#endif //TEAM2025_VARIABLES_GLOBALES_H
