//
// Created by awing on 10/05/2026.
//

#include "Automate.h"

#include "FreeRTOS.h"
#include "FreeRTOS/Source/include/task.h"


void cerveau::automate::init(const Team team) {
    if (team == BLEU) {
        strategie::generateBlueStrat();
    } else {
        strategie::generateYellowStrat();
    }

}

void cerveau::automate::play_match(void *pvParameters) {
    auto *procedure_demarrage = (void (*)()) pvParameters;
    procedure_demarrage();
    strategie::strat->execute();
    vTaskDelete(nullptr);
}
