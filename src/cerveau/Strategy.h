//
// Created by awing on 28/04/2026.
//

#ifndef TEAM2026_STRATEGY_H
#define TEAM2026_STRATEGY_H

#include "cerveau/Tache.h"

inline static Tache::Tache tachesBleu = {
    Tache::Tache{
        .wb_x = {Tache::DELTA, -300},
    }
};

inline static Tache::Tache tachesJaune = {
    Tache::Tache{
        .wb_x = {Tache::DELTA, -300},
    }
};

#endif //TEAM2026_STRATEGY_H
