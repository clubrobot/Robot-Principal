//
// Created by awing on 09/05/2026.
//

#ifndef TEAM2026_STATEMACHINE_H
#define TEAM2026_STATEMACHINE_H
#include <queue>

#include "Node.h"

class StateMachine {
public:
    StateMachine() : startingNode(nullptr) {
    }

    explicit StateMachine(Node *startingNode) : startingNode(startingNode) {
    }

    void setStartingNode(Node *startingNode) {this->startingNode = startingNode;}
    void execute();
protected:
    Node* startingNode;
    std::queue<Node*> activeNodes = {};

};

#endif //TEAM2026_STATEMACHINE_H
