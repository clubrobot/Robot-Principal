//
// Created by awing on 09/05/2026.
//
#include "StateMachine.h"

/**
 * @Brief Execute the grafcet
 * Uses a queue (activeNodes) to keep track of which node are enabled, if they are action nodes do their
 * action and then transition if needed.
 */
void StateMachine::execute() {
    activeNodes.push(startingNode);
    do {
        Node* currentNode = activeNodes.back();
        activeNodes.pop();
        if (!currentNode->isTransition) {
            currentNode->action();
        }
        bool transition = currentNode->synchronize;
        if (currentNode->children == nullptr) continue;
        for (Node **child = currentNode->children; *child != nullptr; child++) {
            if (currentNode->synchronize) {
                transition &= (*child)->enabled();
            } else {
                transition |= (*child)->enabled();
            }
        }
        if (transition) {
            currentNode->active = false;
            for (Node **child = currentNode->children; *child != nullptr; child++) {
                activeNodes.push(*child);
            }
        } else {
            activeNodes.push(currentNode);
        }
    } while (!activeNodes.empty());
}