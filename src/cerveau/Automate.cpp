//
// Created by awing on 28/04/2026.
//
#include "cerveau/Automate.h"

namespace Automate {

    void init(teamColor team) {
        color = team;
        taches = team == JAUNE ? tachesJaune : tachesBleu;
        current_points = 0;
        numberTaches = team == JAUNE ? sizeof(tachesJaune) / sizeof(Tache::Tache): sizeof(tachesBleu) / sizeof(Tache::Tache);
    }

    void playMatch(void *pvParameters) {
        auto *procedure_demarrage = (void (*)()) pvParameters;
        procedure_demarrage();

        for (int i = 0; i < numberTaches; i++) {
            const Tache::Tache* tache = &taches[i];
            if (isClampValid(*tache)) {
                switch (tache->elevator_height.mode) {
                    case Tache::DELTA:
                        Error_Handler(); // On ne gère pas les deltas pour l'ascenseur, seulement les positions absolues
                        break;
                    case Tache::ABSOLUTE:
                        HazelnutGripper::Elevator::setAngle(tache->elevator_height.value);
                        break;
                    default:
                        break;
                } switch (tache->clamp_open.mode) {
                    case Tache::ABSOLUTE:
                        if (tache->clamp_open.value) {
                            HazelnutGripper::Gripper::openAll();
                        } else {
                            HazelnutGripper::Gripper::closeAll();
                        }
                        break;
                    case Tache::DELTA:
                        Error_Handler(); // Comment ca le delta d'un bool
                        break;
                    default:
                        break;
                } switch (tache->clamp_spread.mode) {
                    case Tache::ABSOLUTE:
                        if (tache->clamp_spread.value) {
                            HazelnutGripper::Gripper::spreadFingers(0);
                        } else {
                            HazelnutGripper::Gripper::spreadFingers(180);
                        }
                        break;
                    case Tache::DELTA:
                        Error_Handler(); // Comment ca le delta d'un bool
                        break;
                    default:
                        break;
                } if (tache->clamp_conditionalRotate.mode != Tache::IGNORE) {
                    for (int j = 0; i <= 4; i++) {
                        teamColor c = convertColor(lastColor[j]);
                        if (color != c) {
                            HazelnutGripper::Gripper::getFinger(j).setAngle(1, 180);
                        }
                    }
                } switch (tache->clamp_rotate.mode) {
                    case Tache::DELTA:
                        Error_Handler(); //nuh huh
                        break;
                    case Tache::ABSOLUTE:
                        for (int j = 0; i <= 4; i++) {
                            HazelnutGripper::Gripper::getFinger(j).setAngle(1, 180 * tache->clamp_rotate.value[j]);
                        }
                        break;
                    default:
                        break;
                } switch (tache->clamp_getColor.mode) {
                    case Tache::ABSOLUTE:
                        if (tache->clamp_getColor.value) {
                            for (int j = 0; i <= 4; i++) {
                                HazelnutGripper::ColorData colorData = HazelnutGripper::Gripper::getFinger(j).getColor();
                                lastColor[j] = colorData;
                            }
                        }
                        break;
                    case Tache::DELTA:
                        Error_Handler(); //nuh huh
                        break;
                    default:
                        break;
                }

                errorHandler();
            }
            if (isMovementValid(*tache)) {
                if (tache->wb_theta.mode == Tache::DELTA) {
                    Wheeledbase::TURNTO_DELTA(tache->wb_theta.value, false);
                } else if (tache->wb_x.mode == Tache::DELTA) {
                    Wheeledbase::GOTO_DELTA(tache->wb_x.value, 0, false);
                } else {
                    errorHandler();
                }
            }
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
            while (
                (tache->clamp_open.mode != Tache::IGNORE && allFingerInPos())
            ){}
        }
    }

    bool allFingerInPos() {
        return
            HazelnutGripper::Gripper::getFinger(0).isTargetReached() &&
            HazelnutGripper::Gripper::getFinger(1).isTargetReached() &&
            HazelnutGripper::Gripper::getFinger(2).isTargetReached() &&
            HazelnutGripper::Gripper::getFinger(3).isTargetReached();
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

    teamColor convertColorData(HazelnutGripper::ColorData const &colorData) {
        if (colorData.red > colorData.green && colorData.red > colorData.blue) return JAUNE;
        if (colorData.blue > colorData.red  && colorData.blue > colorData.green) return BLEU;
        errorHandler();
    }

    void errorHandler() {
        automateLogger.log(ERROR_LEVEL, "État invalide (tâche non valide ou couleur ambiguë)!\n");
        while (true) {
            // Boucle infinie pour indiquer une erreur
        }
    }
}
