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
#include "Geogebra.h"

#ifndef ELEVATOR_IN_POS
#define ELEVATOR_IN_POS() (fabs(HazelnutGripper::Elevator::m_currentAngle - HazelnutGripper::Elevator::m_angleSetpoint) < 5)
#endif

namespace cerveau {
    inline auto stratLogger = Logger("STRATEGIE");
}

namespace cerveau::strategie {
    inline ActionNode* yellowStartingNode = {};
    inline ActionNode* bleuStartingNode = {};
    inline auto* strat = new StateMachine();

    //void generateBlueStrat();
    //void generateYellowStrat();

    void stratDeSecoursBleu();
    void stratDeSecoursJaune();

    //checkers


    inline Position start = {};
    inline const Position blueStart;
    inline const Position yellowStart;
}


#endif //TEAM2026_STRATEGIE_H
