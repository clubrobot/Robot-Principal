//
// Created by awing on 10/05/2026.
//

#include "Strategie.h"

#include "Automate.h"
#include "Wheeledbase.h"
#include "Elevator.h"
#include "HazelnutGripper.h"
#include "Geogebra.h"
#include "ihm/ihm.h"

namespace cerveau::strategie {
    void generateBlueStrat() {
        bleuStartingNode = new ActionNode();
        bleuStartingNode->actionFunction = [] {
            HazelnutGripper::Elevator::setAngle(HazelnutGripper::Elevator::HAUT);
            HazelnutGripper::Gripper::closeAll();
        };
        strat->setStartingNode(bleuStartingNode);

        auto *t1 = new Transition();
        t1->condition = [] {
            return ELEVATOR_IN_POS();
        };
        bleuStartingNode->addChild(t1);

        auto *n2 = new ActionNode();
        n2->actionFunction = [] {
            Wheeledbase::GOTO(&positions_bleu[R0L_B], true, PurePursuit::FORWARD, false);
        };
        t1->addChild(n2);

        auto *t2 = new Transition();
        t2->condition = [] {
            return Wheeledbase::POSITION_REACHED() & 0b01;
        };
        n2->addChild(t2);

        auto* tos1 = new ActionNode();
        tos1->actionFunction = [] {
            Wheeledbase::START_TURNONTHESPOT(TurnOnTheSpot::TRIG, positions_bleu[R0L_B].theta);
        };
        t2->addChild(tos1);

        auto* tost1 = new Transition();
        tost1->condition = [] {
            return Wheeledbase::POSITION_REACHED() & 0b01;
        };
        tos1->addChild(tost1);

        auto *n3 = new ActionNode();
        n3->actionFunction = [] {
            HazelnutGripper::Elevator::setAngle(HazelnutGripper::Elevator::CAPTEURS);
        };
        tost1->addChild(n3);

        auto *t3 = new Transition();
        t3->condition = [] {
            return ELEVATOR_IN_POS();
        };
        n3->addChild(t3);

        HazelnutGripper::ColorData colors[4];
        auto *n4 = new ActionNode();
        bool q = false;
        n4->actionFunction = [&colors, &q] {
            for (int i = 0; i < 4; i++) {
                HazelnutGripper::GripperFinger *finger = &HazelnutGripper::Gripper::getFinger(i);
                finger->setSensingMode(HazelnutGripper::OperationMode::SingleRead);
                vTaskDelay(pdMS_TO_TICKS(1300));
                while (!finger->hasNewColorData()) {
                }
                colors[i] = finger->getColor();
                ihm::ihmLogger.log(INFO_LEVEL, "%f, %f, %f", colors[i].red, colors[i].green, colors[i].blue);
            }
            q = true;
        };
        t3->addChild(n4);

        auto *t4 = new Transition();
        t4->condition = [&q] {
            return q;
        };
        n4->addChild(t4);

        auto *n6 = new ActionNode();
        n6->actionFunction = [] {
            HazelnutGripper::Elevator::setAngle(HazelnutGripper::Elevator::CAPTEURS + 10);
            HazelnutGripper::Gripper::openAll();
        };
        t4->addChild(n6);

        auto *t7 = new Transition();
        t7->condition = [] {
            bool t = true;
            for (int i = 0; i < 4; i++) {
                t &= HazelnutGripper::Gripper::getFinger(i).isTargetReached();
            }
            return ELEVATOR_IN_POS() && t;
        };
        n6->addChild(t7);

        auto *n7 = new ActionNode();
        n7->actionFunction = [] {
            Wheeledbase::GOTO(&positions_bleu[R0P_B], false, PurePursuit::FORWARD, false);
        };
        t7->addChild(n7);

        auto *t6 = new Transition();
        t6->condition = [] {
            return Wheeledbase::POSITION_REACHED() & 0b01;
        };
        n7->addChild(t6);

        auto *n8 = new ActionNode();
        n8->actionFunction = [] {
            HazelnutGripper::Elevator::setAngle(HazelnutGripper::Elevator::BAS);
        };
        t6->addChild(n8);

        auto *t8 = new Transition();
        t8->condition = [] {
            return ELEVATOR_IN_POS();
        };
        n8->addChild(t8);

        auto *n9 = new ActionNode();
        n9->actionFunction = [] {
            HazelnutGripper::Gripper::closeAll();
            vTaskDelay(pdMS_TO_TICKS(1000));
        };
        t8->addChild(n9);

        auto *t9 = new Transition();
        t9->condition = [] {
            bool t = true;
            for (int i = 0; i < 4; i++) {
                t &= HazelnutGripper::Gripper::getFinger(i).isTargetReached();
            }
            ihm::ihmLogger.log(INFO_LEVEL, "%d", t);
            return t;
        };
        n9->addChild(t9);

        auto *n12 = new ActionNode();
        n12->actionFunction = [] {
            HazelnutGripper::Elevator::setAngle(HazelnutGripper::Elevator::HAUT);
            HazelnutGripper::Gripper::spreadFingers(180);
        };
        t9->addChild(n12);

        auto *t12 = new Transition();
        t12->condition = [] {
            return ELEVATOR_IN_POS();
        };
        n12->addChild(t12);

        auto *n13 = new ActionNode();
        n13->actionFunction = [&colors] {
            for (int i = 0; i < 4; i++) {
                const auto color = colors[i];
                automate::Team t;
                if (color.red > color.blue) {
                    t = automate::Team::JAUNE; //what red ?
                } else {
                    t = automate::Team::BLEU;
                }
                if (t != automate::ourTeam) {
                    HazelnutGripper::Gripper::getFinger(i).setAngle(1, 180);
                }
            }
        };
        t12->addChild(n13);

        auto *t13 = new Transition();
        t13->condition = [] {
            bool t = true;
            for (int i = 0; i < 4; i++) {
                t |= HazelnutGripper::Gripper::getFinger(i).isTargetReached();
            }
            return t;
        };
        n13->addChild(t13);

        auto *n10 = new ActionNode();
        n10->actionFunction = [] {
            HazelnutGripper::Gripper::spreadFingers(0);
            Wheeledbase::GOTO(&positions_bleu[R0D_B], true, PurePursuit::FORWARD, false);
        };
        t13->addChild(n10);

        auto *t10 = new Transition();
        t10->condition = [] {
            return Wheeledbase::POSITION_REACHED() & 0b01;
        };
        n10->addChild(t10);

        auto *n11 = new ActionNode();
        n11->actionFunction = [] {
            HazelnutGripper::Elevator::setAngle(HazelnutGripper::Elevator::BAS);
        };
        t10->addChild(n11);

        auto *t14 = new Transition();
        t14->condition = [] {
            return ELEVATOR_IN_POS();
        };
        n11->addChild(t14);

        auto *n15 = new ActionNode();
        n15->actionFunction = [] {
            HazelnutGripper::Gripper::openAll();
        };
        t14->addChild(n15);

        auto *t15 = new Transition();
        t15->condition = [] {
            bool t = true;
            for (int i = 0; i < 4; i++) {
                HazelnutGripper::Gripper::getFinger(i).isTargetReached();
            }
            return t;
        };
        n15->addChild(t15);

        auto *n17 = new ActionNode();
        n17->actionFunction = [] {
            HazelnutGripper::Elevator::setAngle(HazelnutGripper::Elevator::BAS);
            vTaskDelay(pdMS_TO_TICKS(201));
            Wheeledbase::GOTO_DELTA(-399, 0, false);
        };
        t15->addChild(n17);

        auto *t16 = new Transition();
        t16->condition = [] {
            return ELEVATOR_IN_POS() && Wheeledbase::POSITION_REACHED() & 0b01;
        };
        n17->addChild(t16);

        auto *n27 = new ActionNode();
        n27->actionFunction = [] {
            Wheeledbase::START_TURNONTHESPOT(false, 3 * PI / 4);
        };
        t16->addChild(n27);

        auto *t17 = new Transition();
        t17->condition = [] {
            return Wheeledbase::POSITION_REACHED() & 0b01;
        };
        n17->addChild(t17);

        auto *n18 = new ActionNode();
        n18->actionFunction = [] {
            Wheeledbase::GOTO(&start, true, PurePursuit::FORWARD, false);
        };
        t17->addChild(n18);

        auto *t19 = new Transition();
        t19->condition = [] {
            return Wheeledbase::POSITION_REACHED() & 0b01;
        };
        n18->addChild(t19);
    }

    void generateYellowStrat() {
        yellowStartingNode = new ActionNode();
        yellowStartingNode->actionFunction = [] {
            HazelnutGripper::Elevator::setAngle(HazelnutGripper::Elevator::HAUT);
            HazelnutGripper::Gripper::closeAll();
        };
        strat->setStartingNode(yellowStartingNode);

        auto *t1 = new Transition();
        t1->condition = [] {
            return ELEVATOR_IN_POS();
        };
        yellowStartingNode->addChild(t1);

        auto *n2 = new ActionNode();
        n2->actionFunction = [] {
            Wheeledbase::GOTO(&positions_bleu[R0L_J], true, PurePursuit::FORWARD, false);
        };
        t1->addChild(n2);

        auto *t2 = new Transition();
        t2->condition = [] {
            return Wheeledbase::POSITION_REACHED() & 0b01;
        };
        n2->addChild(t2);

        auto *n3 = new ActionNode();
        n3->actionFunction = [] {
            HazelnutGripper::Elevator::setAngle(HazelnutGripper::Elevator::CAPTEURS);
        };
        t2->addChild(n3);

        auto *t3 = new Transition();
        t3->condition = [] {
            return ELEVATOR_IN_POS();
        };
        n3->addChild(t3);

        HazelnutGripper::ColorData colors[4];
        auto *n4 = new ActionNode();
        n4->actionFunction = [&colors] {
            for (int i = 0; i < 4; i++) {
                HazelnutGripper::GripperFinger *finger = &HazelnutGripper::Gripper::getFinger(i);
                finger->setSensingMode(HazelnutGripper::OperationMode::SingleRead);
                while (!finger->hasNewColorData()) {
                }
                colors[i] = finger->getColor();
            }
        };
        t3->addChild(n4);

        auto *t4 = new Transition();
        t4->condition = [] {
            return true;
        };
        n4->addChild(t4);

        auto *n6 = new ActionNode();
        n6->actionFunction = [] {
            HazelnutGripper::Elevator::setAngle(HazelnutGripper::Elevator::CAPTEURS + 10);
            HazelnutGripper::Gripper::openAll();
        };
        t4->addChild(n6);

        auto *t7 = new Transition();
        t7->condition = [] {
            bool t = true;
            for (int i = 0; i < 4; i++) {
                t &= !HazelnutGripper::Gripper::getFinger(i).isTargetReached();
            }
            return ELEVATOR_IN_POS() && t;
        };
        n6->addChild(t7);

        auto *n7 = new ActionNode();
        n7->actionFunction = [] {
            Wheeledbase::GOTO(&positions_jaune[R0P_J], false, PurePursuit::FORWARD, false);
        };
        t7->addChild(n7);

        auto *t6 = new Transition();
        t6->condition = [] {
            return Wheeledbase::POSITION_REACHED() & 0b01;
        };
        n7->addChild(t6);

        auto *n8 = new ActionNode();
        n8->actionFunction = [] {
            HazelnutGripper::Elevator::setAngle(HazelnutGripper::Elevator::BAS);
        };
        t6->addChild(n8);

        auto *t8 = new Transition();
        t8->condition = [] {
            return ELEVATOR_IN_POS();
        };
        n8->addChild(t8);

        auto *n9 = new ActionNode();
        n9->actionFunction = [] {
            HazelnutGripper::Gripper::closeAll();
        };
        t8->addChild(n9);

        auto *t9 = new Transition();
        t9->condition = [] {
            bool t = true;
            for (int i = 0; i < 4; i++) {
                t |= HazelnutGripper::Gripper::getFinger(i).isTargetReached();
            }
            return t;
        };
        n9->addChild(t9);

        auto *n12 = new ActionNode();
        n12->actionFunction = [] {
            HazelnutGripper::Elevator::setAngle(HazelnutGripper::Elevator::HAUT);
            HazelnutGripper::Gripper::spreadFingers(180);
        };
        t9->addChild(n12);

        auto *t12 = new Transition();
        t12->condition = [] {
            return ELEVATOR_IN_POS();
        };
        n12->addChild(t12);

        auto *n13 = new ActionNode();
        n13->actionFunction = [&colors] {
            for (int i = 0; i < 4; i++) {
                const auto color = colors[i];
                automate::Team t;
                if (color.red > color.blue) {
                    t = automate::Team::JAUNE;
                } else {
                    t = automate::Team::BLEU;
                }
                if (t != automate::ourTeam) {
                    HazelnutGripper::Gripper::getFinger(i).setAngle(1, 180);
                }
            }
        };
        t12->addChild(n13);

        auto *t13 = new Transition();
        t13->condition = [] {
            bool t = true;
            for (int i = 0; i < 4; i++) {
                t |= HazelnutGripper::Gripper::getFinger(i).isTargetReached();
            }
            return t;
        };
        n13->addChild(t13);

        auto *n10 = new ActionNode();
        n10->actionFunction = [] {
            HazelnutGripper::Gripper::spreadFingers(0);
            Wheeledbase::GOTO(&positions_jaune[R0D_J], true, PurePursuit::FORWARD, false);
        };
        t13->addChild(n10);

        auto *t10 = new Transition();
        t10->condition = [] {
            return Wheeledbase::POSITION_REACHED() & 0b01;
        };
        n10->addChild(t10);

        auto *n11 = new ActionNode();
        n11->actionFunction = [] {
            HazelnutGripper::Elevator::setAngle(HazelnutGripper::Elevator::BAS);
        };
        t10->addChild(n11);

        auto *t14 = new Transition();
        t14->condition = [] {
            return ELEVATOR_IN_POS();
        };
        n11->addChild(t14);

        auto *n15 = new ActionNode();
        n15->actionFunction = [] {
            HazelnutGripper::Gripper::openAll();
        };
        t14->addChild(n15);

        auto *t15 = new Transition();
        t15->condition = [] {
            bool t = true;
            for (int i = 0; i < 4; i++) {
                HazelnutGripper::Gripper::getFinger(i).isTargetReached();
            }
            return t;
        };
        n15->addChild(t15);

        auto *n16 = new ActionNode();
        n16->actionFunction = [] {
            HazelnutGripper::Elevator::setAngle(HazelnutGripper::Elevator::BAS);
            vTaskDelay(pdMS_TO_TICKS(200));
            Wheeledbase::GOTO_DELTA(-400, 0, false);
        };
        t15->addChild(n16);

        auto *t16 = new Transition();
        t16->condition = [] {
            return ELEVATOR_IN_POS() && Wheeledbase::POSITION_REACHED() & 0b01;
        };
        n16->addChild(t16);

        auto *n17 = new ActionNode();
        n17->actionFunction = [] {
            Wheeledbase::START_TURNONTHESPOT(false, 3 * PI / 4);
        };
        t16->addChild(n17);

        auto *t17 = new Transition();
        t17->condition = [] {
            return Wheeledbase::POSITION_REACHED() & 0b01;
        };
        n17->addChild(t17);

        auto *n18 = new ActionNode();
        n18->actionFunction = [] {
            Wheeledbase::GOTO(&start, true, PurePursuit::FORWARD, false);
        };
        t17->addChild(n18);

        auto *t19 = new Transition();
        t19->condition = [] {
            return Wheeledbase::POSITION_REACHED() & 0b01;
        };
        n18->addChild(t19);
    }

    void stratDeSecoursBleu() {
        bleuStartingNode = new ActionNode();
        bleuStartingNode->actionFunction = [] {
            Wheeledbase::GOTO_DELTA(860, 0, false);
        };
        strat->setStartingNode(bleuStartingNode);

        auto* t1 = new Transition();
        t1->condition = [] {
            return Wheeledbase::POSITION_REACHED() & 0b01;
        };
        bleuStartingNode->addChild(t1);

        auto* n2 = new ActionNode();
        n2->actionFunction = [] {
          Wheeledbase::GOTO_DELTA(-400, -100, false);
        };
        t1->addChild(n2);

        auto* t2 = new Transition();
        t2->condition = [] {
            return Wheeledbase::POSITION_REACHED() & 0b01;
        };
        n2->addChild(t2);

        auto* n3 = new ActionNode();
        n3->actionFunction = [] {
            Wheeledbase::GOTO(new Position(2200, 600, PI), true, PurePursuit::FORWARD, false);
        };
        t2->addChild(n3);

        auto* t3 = new Transition();
        t3->condition = [] {
            return Wheeledbase::POSITION_REACHED() & 0b01;
        };
        n3->addChild(t3);

        auto* tos = new ActionNode();
        tos->actionFunction = [] {
            Wheeledbase::START_TURNONTHESPOT(TurnOnTheSpot::TRIG, PI);
        };
        t3->addChild(tos);

        auto* ttos = new Transition();
        ttos->condition = [] {
            return Wheeledbase::POSITION_REACHED() & 0b01;
        };
        tos->addChild(ttos);

        auto* n4 = new ActionNode();
        n4->actionFunction = [] {
            Wheeledbase::GOTO_DELTA(600, 0, false);
        };
        ttos->addChild(n4);

        auto* t4= new Transition();
        t4->condition = [] {
            return Wheeledbase::POSITION_REACHED() & 0b01;
        };
        n4->addChild(t4);

        auto* n5 = new ActionNode();
        n5->actionFunction = [] {
            Wheeledbase::GOTO_DELTA(-700, 0, false);
        };
        t4->addChild(n5);

        auto* t5 = new Transition();
        t5->condition = [] {
            return Wheeledbase::POSITION_REACHED() & 0b01;
        };
        n5->addChild(t5);

        auto* n6 = new ActionNode();
        n6->actionFunction = [] {
            Wheeledbase::GOTO(&start, true, PurePursuit::NONE, false);
        };
        t5->addChild(n6);

        auto* t6 = new Transition();
        t6->condition = [] {
            return Wheeledbase::POSITION_REACHED() & 0b01;
        };
        n6->addChild(t6);
    }

    void stratDeSecoursJaune() {
        yellowStartingNode = new ActionNode();
        yellowStartingNode->actionFunction = [] {
            Wheeledbase::GOTO_DELTA(860, 0, false);
        };
        strat->setStartingNode(yellowStartingNode);

        auto* t1 = new Transition();
        t1->condition = [] {
            return Wheeledbase::POSITION_REACHED() & 0b01;
        };
        yellowStartingNode->addChild(t1);

        auto* n2 = new ActionNode();
        n2->actionFunction = [] {
          Wheeledbase::GOTO_DELTA(-400, -100, false);
        };
        t1->addChild(n2);

        auto* t2 = new Transition();
        t2->condition = [] {
            return Wheeledbase::POSITION_REACHED() & 0b01;
        };
        n2->addChild(t2);

        auto* n3 = new ActionNode();
        n3->actionFunction = [] {
            Wheeledbase::GOTO(new Position(800, 600, 0), true, PurePursuit::FORWARD, false);
        };
        t2->addChild(n3);

        auto* t3 = new Transition();
        t3->condition = [] {
            return Wheeledbase::POSITION_REACHED() & 0b01;
        };
        n3->addChild(t3);

        auto* tos = new ActionNode();
        tos->actionFunction = [] {
            Wheeledbase::START_TURNONTHESPOT(TurnOnTheSpot::TRIG, 0);
        };
        t3->addChild(tos);

        auto* ttos = new Transition();
        ttos->condition = [] {
            return Wheeledbase::POSITION_REACHED() & 0b01;
        };
        tos->addChild(ttos);

        auto* n4 = new ActionNode();
        n4->actionFunction = [] {
            Wheeledbase::GOTO_DELTA(600, 0, false);
        };
        ttos->addChild(n4);

        auto* t4= new Transition();
        t4->condition = [] {
            return Wheeledbase::POSITION_REACHED() & 0b01;
        };
        n4->addChild(t4);

        auto* n5 = new ActionNode();
        n5->actionFunction = [] {
            Wheeledbase::GOTO_DELTA(-700, 0, false);
        };
        t4->addChild(n5);

        auto* t5 = new Transition();
        t5->condition = [] {
            return Wheeledbase::POSITION_REACHED() & 0b01;
        };
        n5->addChild(t5);

        auto* n6 = new ActionNode();
        n6->actionFunction = [] {
            Wheeledbase::GOTO(&start, true, PurePursuit::NONE, false);
        };
        t5->addChild(n6);

        auto* t6 = new Transition();
        t6->condition = [] {
            return static_cast<bool>(Wheeledbase::POSITION_REACHED());
        };
        n6->addChild(t6);

    }
}


///ActionNode* action(auto nf){
///     auto* n = new ActionNode();
///     n->actionFunction = nf
///     return n;
///};

///nf1 = Wheeledbase::GOTO(&positions_bleu[R0L_B], true, PurePursuit::FORWARD, false);
///n1 = action(nf1);
///n1->addChild(t0);


///ActionNode* transition(tf){
///     auto* t = new Transition();
///     t->actionFunction = tf;
///     return t;
///}

///tf1 = Wheelbase::POSITION_REACHED() & 0b01;
///t1 = transition(tf1);
///tf1->addChild(n1);
