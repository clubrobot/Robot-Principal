//
// Created by awing on 28/04/2026.
//
#ifndef TEAM2026_AUTOMATE_H
#define TEAM2026_AUTOMATE_H

#include "Logger.h"
#include "cerveau/Tache.h"
#include "cerveau/Strategy.h"
#include "Wheeledbase.h"

namespace Automate {
    enum color {
        JAUNE,
        BLEU
    };
    typedef color teamColor;

    inline static Logger automateLogger = Logger("Automate");
    inline static Tache::Tache* taches; // Liste de tâches
    inline static color color; // Couleur de l'équipe
    inline static int current_points = 0; // Points réalisés pour l'instant
    inline static int numberTaches = 0; // Nombre de tâches

    void init(teamColor team);
    void playMatch(void *pvParameters);
    [[noreturn]] void errorHandler();
    bool isClampValid(Tache::Tache const &tache);
    bool isMovementValid(Tache::Tache const &tache);
}

#endif //TEAM2026_AUTOMATE_H
