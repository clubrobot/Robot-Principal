//
// Created by Romain Pouvreau on 14/05/2026.
//

#ifndef TEAM2026_KILLER_H
#define TEAM2026_KILLER_H

/**
 * @file Killer.h
 * @ingroup strategy
 * @ingroup core
 * @brief Arrête le robot à la fin du temps imparti
 */

/**
 * @namespace killer
 * @brief Contient les fonctions et variables nécessaires pour gérer l'arrêt du robot à la fin
 */
namespace killer
{
    void killer_loop(void *pvParameters);
}

#endif //TEAM2026_KILLER_H
