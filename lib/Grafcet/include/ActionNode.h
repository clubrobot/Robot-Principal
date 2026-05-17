//
// Created by awing on 09/05/2026.
//

#ifndef TEAM2026_ACTIONNODE_H
#define TEAM2026_ACTIONNODE_H
#include <functional>

#include "Node.h"

namespace Grafcet {
    class ActionNode : public Node {
    public:
        /**
         * @brief An action node is enabled if active
         * @return true if active
         */
        bool enabled() override {return active;}

        /**
         * @brief execute the actionFunction on raising front
         */
        void action() override {
            if (!active) {
                actionFunction();
                active = true;
            }
        }
        /// std::function pointing to the action to realize
        std::function<void()> actionFunction = nullptr;
    };
}
#endif //TEAM2026_ACTIONNODE_H
