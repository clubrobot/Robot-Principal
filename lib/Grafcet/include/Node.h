//
// Created by awing on 09/05/2026.
//

#ifndef TEAM2026_NODE_H
#define TEAM2026_NODE_H

class Node {
public:
    explicit Node(Node** parent = nullptr, Node** child = nullptr) : parent(parent), child(child) {}
    virtual ~Node() = default;
    virtual bool enabled() = 0;
    virtual void action() = 0;
    Node** parent = nullptr;
    Node** children = nullptr;
    bool isTransition = false;
    bool synchronize = false;
    bool active = false;
};

#endif //TEAM2026_NODE_H
