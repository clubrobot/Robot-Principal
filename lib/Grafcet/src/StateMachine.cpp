//
// Created by awing on 09/05/2026.
//
#include "StateMachine.h"

#include <iostream>

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
      for (const auto child : currentNode->children) {
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
      if (currentNode->children.front() != nullptr &&
          currentNode->children.front()->synchronize) {
        for (const auto n : currentNode->children.front()->parent) {
          n->active = false;
          // then we need to remove it from the queue if it there
          const int queueSize = activeNodes.size();
          for (int i = 0; i < queueSize; i++) {
            auto node = activeNodes.front();
            activeNodes.pop();
            if (node != n) {
              activeNodes.push(node);
            }
          }
        }
      }
      for (const auto child : currentNode->children) {
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
