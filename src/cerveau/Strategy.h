//
// Created by awing on 28/04/2026.
//

#ifndef TEAM2026_STRATEGY_H
#define TEAM2026_STRATEGY_H

#include "cerveau/Tache.h"


constexpr inline static Tache::Tache tachesBleu[] = {
    Tache::Tache{
        .wb_x = {Tache::DELTA, 500},
        .elevator_height = {Tache::ABSOLUTE, 30},
        .clamp_open = {Tache::ABSOLUTE, true},
    },
    Tache::Tache{
        .elevator_height = {Tache::ABSOLUTE, 0},
    },
    Tache::Tache{
        .clamp_open = {Tache::ABSOLUTE, false},
    },
    Tache::Tache{
        .elevator_height = {Tache::ABSOLUTE, 60},
        .clamp_spread = {Tache::ABSOLUTE, true},
    },
    Tache::Tache{
        .wb_x = {Tache::DELTA, -500},
        .clamp_rotate = {Tache::ABSOLUTE, {false, true, true, false}},
    },
    Tache::Tache{
        .clamp_spread = {Tache::ABSOLUTE, false},
    }

};

constexpr inline static Tache::Tache tachesJaune[] = {
    Tache::Tache{
        .wb_x = {Tache::DELTA, -300},
    }
};

#endif //TEAM2026_STRATEGY_H
