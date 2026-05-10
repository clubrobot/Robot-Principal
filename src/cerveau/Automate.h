//
// Created by awing on 10/05/2026.
//

#ifndef TEAM2026_AUTOMATE_H
#define TEAM2026_AUTOMATE_H

#include "Strategie.h"

namespace cerveau::automate {

    enum s_Team {
        BLEU,
        JAUNE,
    };
    typedef s_Team Team;

    void init(Team team);
    void play_match(void *pvParameters);
}

#endif //TEAM2026_AUTOMATE_H
