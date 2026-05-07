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
    /// Hashmap des labels
    inline static std::unordered_map<String, Tache::Tache> labelMap = {};
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

    /**
     * @brief Initialise l'automate de décision du robot.
     * @param team La couleur de l'équipe pour laquelle initialiser l'automate
     */
    void init(teamColor team);

    /**
     * @brief Fonction principale de l'automate, à exécuter dans une tâche FreeRTOS dédiée.
     * Parse la liste des variables à modifier et appelle les fonctions appropriées pour que les actions soient effectuées
     * @param pvParameters Pointeur vers la fonction qui prépare le robot au début du match
     */
    void playMatch(void *pvParameters);

    /**
     * @brief Gestionnaire d'erreurs pour l'automate, à appeler en cas de problème critique nécessitant l'arrêt du robot.
     */
    [[noreturn]] void errorHandler();

    /**
     * @brief vérifie si une tache inclu un mouvement de pince valide
     * @param tache la tache à tester
     * @return si un mouvement de pince est nécessaire
     */
    bool isClampValid(Tache::Tache const &tache);

    /**
     * @brief vérifie si la tache nécessite un déplacement
     * @param tache la tache à tester
     * @return si un déplacement est nécessaire
     */
    bool isMovementValid(Tache::Tache const &tache);

    /**
     * @brief Vérifie si tout les doigts ont fini de bouger
     * @return si tous les doigts ont fini de bouger
     */
    bool allFingerInPos();

    /**
     * @brief vérifie si l'élévateur est en position
     * @return si l'élévateur est en position
     */
    bool elevatorInPos ();

    /**
     * @brief convertit les données brutes de couleur en couleur d'équipe
     * @param colorData les données de couleur brutes lues par les capteurs de couleur des doigts
     * @return la couleur lue
     */
    teamColor convertColor(HazelnutGripper::ColorData const &colorData);
}

#endif //TEAM2026_AUTOMATE_H
