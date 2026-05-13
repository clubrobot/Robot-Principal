//
// Created by awing on 10/05/2026.
//

#include "Automate.h"

#include "FreeRTOS.h"
#include "Wheeledbase.h"
#include "FreeRTOS/Source/include/task.h"

void procedure_demarrage(){

    cerveau::automate::init(cerveau::automate::JAUNE);
    cerveau::automate::automateLogger.log(INFO_LEVEL,"Le robot est armé!\n");

    //Detect tirette
    /**while(etat_tirette()==1){}
    main_logs.log(WARNING_LEVEL,"tirette mise !\n");
    while (etat_tirette()==0){}
    main_logs.log(WARNING_LEVEL,"tirette enlevée !\n");*/

}

void cerveau::automate::init(const Team team) {
    if (team == BLEU) {
        strategie::start = strategie::blueStart;
        strategie::generateBlueStrat();
    } else {
        strategie::start = strategie::yellowStart;
        strategie::generateYellowStrat();
    }
    Wheeledbase::SET_POSITION(&strategie::start);
}

void cerveau::automate::play_match(void *pvParameters) {
    procedure_demarrage();
    strategie::strat->execute();
    vTaskDelete(nullptr);
}
