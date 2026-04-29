//
// Created by awing on 28/04/2026.
//
#ifndef TEAM2026_AUTOMATE_H
#define TEAM2026_AUTOMATE_H

#include "Logger.h"
#include "cerveau/Tache.h"
#include "cerveau/Strategy.h"
#include "HazelnutGripper.h"
#include "GripperFinger.h"
#include "Elevator.h"
#include "Wheeledbase.h"

namespace Automate {
    enum s_color {
        JAUNE,
        BLEU
    };
    typedef s_color teamColor;

    inline static Logger automateLogger = Logger("Automate");
    inline static const Tache::Tache *taches; // Liste de tâches
    inline static s_color color; // Couleur de l'équipe
    inline static int current_points = 0; // Points réalisés pour l'instant
    inline static int numberTaches = 0; // Nombre de tâches
    inline static HazelnutGripper::ColorData lastColor[4] = {}; // Dernières données de couleur lues par les doigts

    void init(teamColor team);
    void playMatch(void *pvParameters);
    [[noreturn]] void errorHandler();
    bool isClampValid(Tache::Tache const &tache);
    bool isMovementValid(Tache::Tache const &tache);
    teamColor convertColor(HazelnutGripper::ColorData colorData);
}

#endif //TEAM2026_AUTOMATE_H
