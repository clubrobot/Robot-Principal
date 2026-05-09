//
// Created by awing on 09/05/2026.
//

#ifndef TEAM2026_TRANSITION_H
#define TEAM2026_TRANSITION_H
#include "Node.h"

class Transition : Node {
public:
    void action() override {}
    bool enabled() override {
        bool parentReady = true;
        for (Node **node = parent; node != nullptr; node++) {
            parentReady &= (*node)->enabled();
        }
        if (condition == nullptr) return false;
        return condition() & (parentReady | synchronize);
    }
    bool transition = true;
    bool (*condition)() = nullptr;
};

#endif //TEAM2026_TRANSITION_H
