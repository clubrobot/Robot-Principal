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
        transition1->condition = elevatorInPos;
        blueStartingNode->addChild(transition1);

        auto* gotoNode1 = new ActionNode();
        gotoNode1->actionFunction = [] {
            Wheeledbase::GOTO(new Position(800, 400, 0), true, PurePursuit::FORWARD, 0, false);
        };
        transition1->addChild(gotoNode1);

        auto* transition2 = new Transition();
        transition2->condition = [] {
            return static_cast<bool>(Wheeledbase::POSITION_REACHED() & 0b01);
        };
        gotoNode1->addChild(transition2);

        auto* elevatorNode2 = new ActionNode();
        elevatorNode2->actionFunction = [] {
            HazelnutGripper::Elevator::setAngle(130);
        };
        transition2->addChild(elevatorNode2);

        auto* transition3 = new Transition();
        transition3->condition = elevatorInPos;
        elevatorNode2->addChild(transition3);

        auto* gotoNode2 = new ActionNode();
        gotoNode2->actionFunction = [] {
            Wheeledbase::GOTO(new Position(800, 200, 0), true, PurePursuit::BACKWARD, 0, false);
        };
        transition3->addChild(gotoNode2);

        auto* elevatorNode3 = new ActionNode();
        elevatorNode2->actionFunction = [] {
            HazelnutGripper::Elevator::setAngle(62);
        };
        transition3->addChild(elevatorNode3);

        auto* transition4 = new Transition();
        transition4->condition = [] {
            return static_cast<bool>(Wheeledbase::POSITION_REACHED() & 0b11) && elevatorInPos();
        };
        transition4->synchronize = true;
        gotoNode2->addChild(transition4);
        elevatorNode3->addChild(transition4);

        auto* endNode = new ActionNode();
        endNode->actionFunction = [] {
            printf("Stratégie terminée !\n");
        };
        transition4->addChild(endNode);
    }

    void generateYellowStrat() {
        yellowStartingNode = new ActionNode();
        yellowStartingNode->actionFunction = [] {
        };
        strat->setStartingNode(yellowStartingNode);
    }

    bool elevatorInPos(){
        return fabs(HazelnutGripper::Elevator::m_encoder->getAngle() - HazelnutGripper::Elevator::m_angle) < 1;
    };
}
