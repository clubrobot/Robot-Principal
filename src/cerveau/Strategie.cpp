//
// Created by awing on 10/05/2026.
//

#include "Strategie.h"
#include "Wheeledbase.h"
#include "Elevator.h"
#include "HazelnutGripper.h"

namespace cerveau::strategie {
    void generateBlueStrat() {
        blueStartingNode = new ActionNode();

        blueStartingNode->actionFunction = [] {
          HazelnutGripper::Elevator::setAngle(62);
        };
        strat->setStartingNode(blueStartingNode);

        auto* transition1 = new Transition();
        transition1->condition = [] {
            return ELEVATOR_IN_POS();
        };
        blueStartingNode->addChild(transition1);

        auto* gotoNode1 = new ActionNode();
        gotoNode1->actionFunction = [] {
            Wheeledbase::GOTO(new Position(1250, 1600, 90), true, PurePursuit::FORWARD, 0, false);
            stratLogger.log(INFO_LEVEL, "Goto 1 lancé\n");
        };
        transition1->addChild(gotoNode1);

        auto* transition2 = new Transition();
        transition2->condition = [] {
            stratLogger.log(INFO_LEVEL, "transition evaluated");
            return static_cast<bool>(Wheeledbase::POSITION_REACHED() & 0b01);
        };
        gotoNode1->addChild(transition2);

        auto* elevatorNode2 = new ActionNode();
        elevatorNode2->actionFunction = [] {
            HazelnutGripper::Elevator::setAngle(130);
            stratLogger.log(INFO_LEVEL, "Elevator set angle \n");
        };
        transition2->addChild(elevatorNode2);

        auto* transition3 = new Transition();
        transition3->condition = [] {
            return ELEVATOR_IN_POS();
        };
        elevatorNode2->addChild(transition3);

        auto* gotoNode2 = new ActionNode();
        gotoNode2->actionFunction = [] {
            stratLogger.log(INFO_LEVEL, "Goto 2 lancé\n");
            Wheeledbase::GOTO(new Position(1250, 1400, PI/2), true, PurePursuit::BACKWARD, PI/2, false);
        };
        transition3->addChild(gotoNode2);

        auto* elevatorNode3 = new ActionNode();
        elevatorNode3->actionFunction = [] {
            stratLogger.log(INFO_LEVEL, "Elevator set angle \n");
            HazelnutGripper::Elevator::setAngle(62);
        };
        transition3->addChild(elevatorNode3);

        auto* transition4 = new Transition();
        transition4->condition = [] {
            stratLogger.log(INFO_LEVEL, "transition 4 evaluated");
            return static_cast<bool>(Wheeledbase::POSITION_REACHED() & 0b11) && ELEVATOR_IN_POS();
        };
        transition4->synchronize = true;
        gotoNode2->addChild(transition4);
        elevatorNode3->addChild(transition4);

        auto* returnNode = new ActionNode();
        returnNode->actionFunction = [] {
            stratLogger.log(INFO_LEVEL, "Goto return lancé\n");
            Wheeledbase::GOTO(&start, true, PurePursuit::FORWARD, PI/2, false);
        };
        transition4->addChild(returnNode);

        auto* transition5 = new Transition();
        transition5->condition = [] {
            stratLogger.log(INFO_LEVEL, "transition 5 evaluated");
            return static_cast<bool>(Wheeledbase::POSITION_REACHED() & 0b11);
        };
        returnNode->addChild(transition5);

        auto* endNode = new ActionNode();
        endNode->actionFunction = [] {
            stratLogger.log(INFO_LEVEL, "Stratégie terminée\n");
            printf("Stratégie terminée !\n");
        };
        transition5->addChild(endNode);
    }

    void generateYellowStrat() {
        yellowStartingNode = new ActionNode();
        yellowStartingNode->actionFunction = [] {
        };
        strat->setStartingNode(yellowStartingNode);
    }
}
