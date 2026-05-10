//
// Created by awing on 09/05/2026.
//

#ifndef TEAM2026_NODE_H
#define TEAM2026_NODE_H

class StateMachine;

class Node {
public:
    explicit Node(const std::pmr::vector<Node*> &parent = {}, const std::pmr::vector<Node*> &child = {}) : parent(parent), children(child) {}
    virtual ~Node() = default;
    virtual bool enabled() = 0;
    virtual void action() = 0;
    void addChild(Node *child) {
        this->children.push_back(child);
        child->parent.push_back(this);
    }
    bool isTransition = false;
    bool synchronize = false;
    bool active = false;
protected:
    std::pmr::vector<Node*> parent = {};
    std::pmr::vector<Node*> children = {};

    friend StateMachine;
};

#endif //TEAM2026_NODE_H
