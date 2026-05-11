//
// Created by awing on 10/05/2026.
//

#ifndef TEAM2026_STRATEGIE_H
#define TEAM2026_STRATEGIE_H

#include "Grafcet.h"
#include "Logger.h"
#include "Odometry.h"

namespace cerveau {
    inline auto stratLogger = Logger("STRATEGIE");
}

namespace cerveau::strategie {
    inline ActionNode* yellowStartingNode = {};
    inline ActionNode* blueStartingNode = {};
    inline auto* strat = new StateMachine();

    void generateBlueStrat();
    void generateYellowStrat();

    //checkers

    bool elevatorInPos();

    inline Position start = {};
    inline const Position blueStart = {1500, 300, PI/2};
    inline const Position yellowStart = {0, 0, 0};
}


#endif //TEAM2026_STRATEGIE_H
