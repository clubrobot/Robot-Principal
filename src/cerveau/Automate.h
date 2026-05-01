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
    /**
     * @brief Espace de noms regroupant les fonctions et variables liées à l'automate de décision du robot.
     */

    enum s_color {
        /**
         * @brief Les couleurs d'équipe
         */
        JAUNE,
        BLEU
    };
    typedef s_color teamColor;

    /// Logger dédié à l'automate pour faciliter le débogage et le suivi des actions.
    inline static Logger automateLogger = Logger("Automate");
    /// Listes de tâches pré-définies pour chaque équipe, à remplir dans Strategy.h
    inline static const Tache::Tache *taches = {}; // Liste de tâches
    /// La couleur de l'équipe
    inline static s_color color = {}; // Couleur de l'équipe
    /// Variables de suivi de l'état du match
    inline static int current_points = 0; // Points réalisés pour l'instant
    /// Nombre total de tâches à exécuter
    inline static int numberTaches = 0; // Nombre de tâches
    /// La dernière couleur relevée par le robot
    inline static HazelnutGripper::ColorData lastColor[4] = {}; // Dernières données de couleur lues par les doigts
    /// Précision de l'élevateur en °
    inline static float elevator_precision = 2;

    void init(teamColor team);
    void playMatch(void *pvParameters);
    [[noreturn]] void errorHandler();
    bool isClampValid(Tache::Tache const &tache);
    bool isMovementValid(Tache::Tache const &tache);
    bool allFingerInPos();
    bool elevatorInPos ();
    teamColor convertColor(HazelnutGripper::ColorData const &colorData);
}

#endif //TEAM2026_AUTOMATE_H
