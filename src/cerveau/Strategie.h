//
// Created by awing on 10/05/2026.
//

#ifndef TEAM2026_STRATEGIE_H
#define TEAM2026_STRATEGIE_H

#include "Grafcet.h"

namespace cerveau::strategie {
    inline ActionNode* yellowStartingNode = {};
    inline ActionNode* blueStartingNode = {};
    inline StateMachine* strat = {};

    void generateBlueStrat();
    void generateYellowStrat();

    //checkers

    bool elevatorInPos();
}


#endif //TEAM2026_STRATEGIE_H
