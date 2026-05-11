//
// Created by awing on 09/05/2026.
//

#ifndef TEAM2026_STATEMACHINE_H
#define TEAM2026_STATEMACHINE_H

#include "GrafcetConfig.h"
#include "SimpleQueue.h"
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
    Node* startingNode = nullptr;
    SimpleQueue<Node*, GRAFCET_MAX_QUEUE_SIZE> activeNodes = {};

};

#endif //TEAM2026_STATEMACHINE_H
