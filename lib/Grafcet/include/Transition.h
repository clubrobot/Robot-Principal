//
// Created by awing on 09/05/2026.
//

#ifndef TEAM2026_TRANSITION_H
#define TEAM2026_TRANSITION_H
#include "Node.h"

class Transition : public Node {
public:
    Transition() {
        isTransition = true;
    }
    void action() override {}
    bool enabled() override {
        bool parentReady = synchronize;
        for (const auto node : this->parent) {
            if (synchronize) parentReady &= node->enabled();
            else parentReady |= node->enabled();
        }
        if (condition == nullptr) return false;
        return condition() && (parentReady || synchronize);
    }
    bool (*condition)() = nullptr;
};

#endif //TEAM2026_TRANSITION_H
