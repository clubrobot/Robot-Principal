//
// Created by awing on 28/04/2026.
//
#include "cerveau/Automate.h"

namespace Automate {

    void init(teamColor team) {
        color = team;
        taches = &(team == JAUNE ? tachesJaune : tachesBleu);
        current_points = 0;
        numberTaches = sizeof(team == JAUNE ? tachesJaune : tachesBleu) / sizeof(Tache::Tache);
    }

    void playMatch(void *pvParameters) {
        auto *procedure_demarrage = (void (*)()) pvParameters;
        procedure_demarrage();

        for (int i = 0; i < numberTaches; i++) {
            Tache::Tache* tache = &taches[i];

            if (isClampValid(*tache)) {
                errorHandler();
            }

            if (isMovementValid(*tache)) {
                if (tache->wb_theta.mode == Tache::DELTA) {
                    Wheeledbase::TURNTO_DELTA(tache->wb_theta.value);
                } else if (tache->wb_x.mode == Tache::DELTA) {
                    Wheeledbase::GOTO_DELTA(tache->wb_x.value, 0, false);
                } else {
                    errorHandler();
                }
            }
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        }
    }

    bool isMovementValid(Tache::Tache const &tache) {
        return
                (
                    (
                        (tache.wb_x.mode == Tache::DELTA && tache.wb_y.mode == Tache::IGNORE) ||
                        //si x est delta ou si y est delta
                        (tache.wb_x.mode == Tache::IGNORE && tache.wb_y.mode == Tache::DELTA) ||
                        (
                            (tache.wb_x.mode == Tache::ABSOLUTE || tache.wb_x.mode == Tache::IGNORE) &&
                            //si l'un ou les deux sont absolus
                            (tache.wb_y.mode == Tache::ABSOLUTE || tache.wb_y.mode == Tache::IGNORE)
                        ) //et il faut qu'il n'y ait pas de rotation
                    ) && tache.wb_theta.mode == Tache::IGNORE) ||
                (tache.wb_theta.mode != Tache::IGNORE && tache.wb_x.mode == Tache::IGNORE && tache.wb_y.mode == Tache::IGNORE);
        //si il y a une rotation alors il ne doit pas y avoir de translation
    }

    bool isClampValid(Tache::Tache const &tache) {
        return
            tache.elevator_height.mode != Tache::IGNORE ||
            tache.clamp_getColor.mode != Tache::IGNORE ||
            tache.clamp_open.mode != Tache::IGNORE ||
            tache.clamp_spread.mode != Tache::IGNORE ||
            tache.clamp_rotate.mode != Tache::IGNORE;

    }

    void errorHandler() {
        automateLogger.log(ERROR_LEVEL, "Tache invalide détectée !\n");
        while (true) {
            // Boucle infinie pour indiquer une erreur
        }
    }
}
