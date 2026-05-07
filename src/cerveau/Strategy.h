//
// Created by awing on 28/04/2026.
//

#ifndef TEAM2026_STRATEGY_H
#define TEAM2026_STRATEGY_H

#include "cerveau/Tache.h"


inline static const Tache::Tache tachesBleu[] = {
    Tache::Tache{
        .index = 0,
        .wb_x = {Tache::DELTA, 100},
        .wb_blocking = {Tache::ABSOLUTE, true},
        .elevator_height = {Tache::ABSOLUTE, 80},
    },
    Tache::Tache{
        .index = 1,
        .elevator_height = {Tache::ABSOLUTE, 132.187500},
    },
    Tache::Tache{
        .index = 2,
        .clamp_open = {Tache::ABSOLUTE, false},
    },
    Tache::Tache{
        .index = 3,
        .elevator_height = {Tache::ABSOLUTE, 80},
        .clamp_spread = {Tache::ABSOLUTE, true},
    },
    Tache::Tache{
        .index = 4,
        .wb_x = {Tache::DELTA, -500},
        .clamp_rotate = {Tache::ABSOLUTE, {false, true, true, false}},
    },
    Tache::Tache{
        .index = 5,
        .wb_blocking = {Tache::ABSOLUTE, true},
        .clamp_spread = {Tache::ABSOLUTE, false},
    }

};

inline static const Tache::Tache tachesJaune[] = {
    Tache::Tache{
        .index = 0,
        .wb_x = {Tache::DELTA, -300},
    }
};

#endif //TEAM2026_STRATEGY_H
