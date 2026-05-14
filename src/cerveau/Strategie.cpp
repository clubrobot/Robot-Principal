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
            HazelnutGripper::Elevator::setAngle(HazelnutGripper::Elevator::m_maxRange);
            stratLogger.log(INFO_LEVEL, "Stratégie bleue démarrée\n");
        };
        strat->setStartingNode(blueStartingNode);

        auto* transition1 = new Transition();
        transition1->condition = [] {
            return ELEVATOR_IN_POS();
        };
        blueStartingNode->addChild(transition1);

        auto* gotoNode1 = new ActionNode();
        gotoNode1->actionFunction = [] {
            Wheeledbase::GOTO(new Position(1250, 1600, PI/2), true, PurePursuit::FORWARD, false);
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
            HazelnutGripper::Elevator::setAngle(10);
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
            Wheeledbase::GOTO(new Position(1250, 1400, PI/2), false, PurePursuit::BACKWARD, false);
        };
        transition3->addChild(gotoNode2);

        auto* elevatorNode3 = new ActionNode();
        elevatorNode3->actionFunction = [] {
            stratLogger.log(INFO_LEVEL, "Elevator set angle \n");
            HazelnutGripper::Elevator::setAngle(HazelnutGripper::Elevator::m_maxRange);
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
            Wheeledbase::GOTO(&start, false, PurePursuit::FORWARD, false);
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
        };
        transition5->addChild(endNode);
    }

    void generateYellowStrat() {
        yellowStartingNode = new ActionNode();
        yellowStartingNode->actionFunction = [] {
            HazelnutGripper::Elevator::setAngle(HazelnutGripper::Elevator::HAUT);
        };
        strat->setStartingNode(yellowStartingNode);

        auto* t1 = new Transition();
        t1->condition = [] {
            return ELEVATOR_IN_POS();
        };
        yellowStartingNode->addChild(t1);

        auto* n2 = new ActionNode();
        n2->actionFunction = [] {
            Wheeledbase::GOTO(new Position(200, 0, 0), false, PurePursuit::FORWARD, false);
        };
        t1->addChild(n2);

        auto* t2 = new Transition();
        t2->condition = [] {
            return Wheeledbase::POSITION_REACHED() & 0b01;
        };
        n2->addChild(t2);

        auto* n3 = new ActionNode();
        n3->actionFunction = [] {
            HazelnutGripper::Elevator::setAngle(HazelnutGripper::Elevator::BAS);
        };
        t2->addChild(n3);

        auto* t3 = new Transition();
        t3->condition = [] {
            return ELEVATOR_IN_POS();
        };
        n3->addChild(t3);

        auto* n4 = new ActionNode();
        n4->actionFunction = [] {
            HazelnutGripper::Elevator::setAngle(HazelnutGripper::Elevator::HAUT);
        };
        t3->addChild(n4);

        auto* t4 = new Transition();
        t4->condition = [] {
            return ELEVATOR_IN_POS();
        };
        n4->addChild(t4);

        auto* n5 = new ActionNode();
        n5->actionFunction = [] {
            Wheeledbase::GOTO(&start, false, PurePursuit::BACKWARD, false);
        };
        t4->addChild(n5);

        auto* t6 = new Transition();
        t6->condition = [] {
            return Wheeledbase::POSITION_REACHED() & 0b01;
        };
        n5->addChild(t6);


    }
}
