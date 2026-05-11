//
// Created by awing on 10/05/2026.
//

#ifndef TEAM2026_STRATEGIE_H
#define TEAM2026_STRATEGIE_H

#include "Elevator.h"
#include "Grafcet.h"
#include "HazelnutGripper.h"
#include "Logger.h"
#include "Odometry.h"

#ifndef ELEVATOR_IN_POS
#define ELEVATOR_IN_POS() (HazelnutGripper::Elevator::m_currentAngle - HazelnutGripper::Elevator::m_angle < 1)
#endif

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

    inline Position start = {};
    inline const Position blueStart = {1500, 300, PI/2};
    inline const Position yellowStart = {0, 0, 0};
}


#endif //TEAM2026_STRATEGIE_H
