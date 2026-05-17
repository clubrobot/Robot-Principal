//
// Created by awing on 09/05/2026.
//

#ifndef TEAM2026_STATEMACHINE_H
#define TEAM2026_STATEMACHINE_H
#include <deque>
#include <memory_resource>

#include "Node.h"
namespace Grafcet {
    class StateMachine {
    public:
        StateMachine() = default;
        explicit StateMachine(Node *startingNode) : startingNode(startingNode) {}

        /**
         * @brief Set the starting node of the grafcet.
         * @param startingNode
         */
        void setStartingNode(Node *startingNode) {this->startingNode = startingNode;}

        /**
         * @brief Execute the grafcet
         * Uses a queue (activeNodes) to keep track of which node are enabled, if they
         * are action nodes do their action and then transition if needed.
         */
        void execute();
    protected:
        Node* startingNode = nullptr;
        std::deque<Node*> activeNodes = {};
    };
}
#endif //TEAM2026_STATEMACHINE_H
