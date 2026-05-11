//
// Created by awing on 09/05/2026.
//

#ifndef TEAM2026_NODE_H
#define TEAM2026_NODE_H

#include "GrafcetConfig.h"
#include "SimpleArray.h"

class StateMachine;

class Node {
public:
    Node() = default;
    virtual ~Node() = default;
    virtual bool enabled() = 0;
    virtual void action() = 0;

    void addChild(Node *child) {
        if (!children.push_back(child)) {
            return;
        }
        child->parent.push_back(this);
    }

    bool isTransition = false;
    bool synchronize = false;
    bool active = false;

protected:
    SimpleArray<Node*, GRAFCET_MAX_NODE_PARENTS> parent;
    SimpleArray<Node*, GRAFCET_MAX_NODE_CHILDREN> children;

    friend StateMachine;
};

#endif //TEAM2026_NODE_H
