//
// Created by awing on 10/05/2026.
//

#include "Strategie.h"

namespace cerveau::strategie {
    void generateBlueStrat() {
        blueStartingNode = new ActionNode();
        blueStartingNode->actionFunction = [] {

        };
        strat->setStartingNode(blueStartingNode);
    }

    void generateYellowStrat() {
        yellowStartingNode = new ActionNode();
        yellowStartingNode->actionFunction = [] {
        };
        strat->setStartingNode(yellowStartingNode);
    }
}
