//
// Created by awing on 09/05/2026.
//

#ifndef TEAM2026_TRANSITION_H
#define TEAM2026_TRANSITION_H
#include <functional>

#include "Node.h"
namespace Grafcet {
    class Transition : public Node {
    public:
        Transition() {
            isTransition = true;
        }

        /**
         * @brief transition does nothing
         */
        void action() override {}

        /**
         * @brief evaluate if the transition is enabled using the condition function, and the state of its parent
         * will wait for all of its parent to be enabled if synchronize is true
         * @return true if the transition is enabled
         */
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
        /// std::function pointing toward a function returning true if the condition for the transition to be enabled is realized
        std::function<bool()> condition = {};
    };
}
#endif //TEAM2026_TRANSITION_H
