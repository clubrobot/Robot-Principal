//
// Created by awing on 09/05/2026.
//

#ifndef TEAM2026_ACTIONNODE_H
#define TEAM2026_ACTIONNODE_H
#include "Node.h"

class ActionNode : public Node {
public:
    bool enabled() override {return active;}
    void action() override {
        if (!active) {
            actionFunction();
            active = true;
        }
    }
    void (*actionFunction)() = nullptr;
};

#endif //TEAM2026_ACTIONNODE_H
