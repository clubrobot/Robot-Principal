//
// Created by awing on 10/05/2026.
//

/**
 * @file Automate.h
 * @ingroup strategy
 * @ingroup core
 * @brief Contient le code nécessaire pour jouer un match.
 */

#ifndef TEAM2026_AUTOMATE_H
#define TEAM2026_AUTOMATE_H

#include "Strategie.h"

namespace cerveau::automate {
    inline auto automateLogger = Logger("AUTOMATE");
    enum s_Team {
        BLEU,
        JAUNE,
    };
    typedef s_Team Team;
    inline Team ourTeam;

    void init(Team team);
    void play_match(void *pvParameters);
}

#endif //TEAM2026_AUTOMATE_H
