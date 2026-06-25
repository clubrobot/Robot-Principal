//
// Created by awing on 09/05/2026.
//
/**
 * @file Node.h
 * @ingroup grafcet
 * @brief Représentation d'un noeud du grafcet
 */
#ifndef TEAM2026_NODE_H
#define TEAM2026_NODE_H

#include <vector>
#include <memory_resource>

namespace Grafcet {
    class StateMachine;

    class Node {
    public:
        explicit Node(const std::pmr::vector<Node*> &parent = {}, const std::pmr::vector<Node*> &child = {}) : parent(parent), children(child) {}
        virtual ~Node() = default;
        virtual bool enabled() = 0;
        virtual void action() = 0;

        /**
         * @brief attach a child node to the current node
         * @param child
         */
        void addChild(Node *child) {
            this->children.push_back(child);
            child->parent.push_back(this);
        }

        /// true if the current node is a transition
        bool isTransition = false;
        /// true if the current node needs to wait for all its parent to be enabled before executing
        bool synchronize = false;
        /// true if the node is currently active
        bool active = false;
    protected:
        /// List of parents node of the current node
        std::pmr::vector<Node*> parent = {};
        /// List of children node of the current node
        std::pmr::vector<Node*> children = {};

        friend StateMachine;
    };
}
#endif //TEAM2026_NODE_H
