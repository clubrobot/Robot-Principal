//
// Created by awing on 09/05/2026.
//
#include "StateMachine.h"

/**
 * @Brief Execute the grafcet
 * Uses a queue (activeNodes) to keep track of which node are enabled, if they
 * are action nodes do their action and then transition if needed.
 */
void StateMachine::execute() {
  if (startingNode == nullptr) {
    printf("NO STARTING STATE\n");
    return;
  }
  activeNodes.push(startingNode);
  do {
    Node *currentNode = activeNodes.front();
    activeNodes.pop();
    bool transition = currentNode->synchronize;
    if (!currentNode->isTransition) {
      currentNode->action();
      if (currentNode->children.empty())
        continue;
      for (int i = 0; i < currentNode->children.size(); ++i) {
        Node* child = currentNode->children[i];
        if (currentNode->synchronize) {
          transition &= child->enabled();
        } else {
          transition |= child->enabled();
        }
      }
    } else {
      transition = true;
    }
    if (transition) {
      currentNode->active = false;
      // when the child a syncing transition, its parent need to be deactivated
      // and purge from the queue
      if (!currentNode->children.empty() &&
          currentNode->children[0] != nullptr &&
          currentNode->children[0]->synchronize) {
        for (int i = 0; i < currentNode->children[0]->parent.size(); ++i) {
          Node* n = currentNode->children[0]->parent[i];
          n->active = false;
          // then we need to remove it from the queue if it there
          const int queueSize = activeNodes.size();
          for (int q = 0; q < queueSize; q++) {
            Node* node = activeNodes.front();
            activeNodes.pop();
            if (node != n) {
              activeNodes.push(node);
            }
          }
        }
      }
      for (int i = 0; i < currentNode->children.size(); ++i) {
        Node* child = currentNode->children[i];
        if (!child->isTransition) {
          activeNodes.push(child);
        } else if (child->enabled()) {
          activeNodes.push(child);
        }
      }
    } else {
      activeNodes.push(currentNode);
    }
  } while (!activeNodes.empty());
  printf("state machine empty\n");
}
