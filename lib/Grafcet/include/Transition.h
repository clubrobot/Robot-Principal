//
// Created by awing on 09/05/2026.
//

#ifndef TEAM2026_TRANSITION_H
#define TEAM2026_TRANSITION_H
#include <functional>

#include "Node.h"

class Transition : public Node {
public:
    Transition() {
        isTransition = true;
    }
    void action() override {}
    bool enabled() override {
        bool parentReady = synchronize;
        for (int i = 0; i < parent.size(); ++i) {
            Node* node = parent[i];
            if (synchronize) parentReady &= node->enabled();
            else parentReady |= node->enabled();
        }
        if (condition == nullptr) return false;
        volatile const auto t = condition();
        return condition() && parentReady;
    }
    std::function<bool()> condition = {};
};

#endif //TEAM2026_TRANSITION_H
