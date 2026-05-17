//
// Created by awing on 09/05/2026.
//
#include "StateMachine.h"

#include <iostream>

namespace Grafcet {
  void StateMachine::execute() {
    if (startingNode == nullptr) {
      printf("NO STARTING STATE\n");
      return;
    }
    activeNodes.push_back(startingNode);
    do {
      Node *currentNode = activeNodes.front();
      activeNodes.pop_front();
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
        // Si le premier enfant est une transition synchronisante, on désactive
        // ses parents et on les retire de la file, comme dans l'implémentation
        // originale. On vérifie d'abord qu'il y a bien un enfant.
        if (!currentNode->children.empty() &&
            currentNode->children.front() != nullptr &&
            currentNode->children.front()->synchronize) {
          for (const auto n : currentNode->children.front()->parent) { //FIXME: Currently can't have multiple transition child if one is synchronized
            n->active = false;
            // then we need to remove it from the queue if it there
            std::erase(activeNodes, n);
          }
            }
        for (const auto child : currentNode->children) {
          if (!child->isTransition) {
            activeNodes.push_back(child);
          }
          if (child->isTransition && child->enabled()) { //FIXME: Weirdly fail to add active transition
            activeNodes.push_back(child);
          }
        }
        currentNode->active = false;
      } else {
        activeNodes.push_back(currentNode);
      }
    } while (!activeNodes.empty());
    printf("state machine empty\n");
  }
}