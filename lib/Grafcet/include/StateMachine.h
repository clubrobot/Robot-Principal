//
// Created by awing on 09/05/2026.
//
/**
 * @file StateMachine.h
 * @ingroup grafcet
 * @brief La machine a état permettant de parcourir le grafcet
 */

#ifndef TEAM2026_STATEMACHINE_H
#define TEAM2026_STATEMACHINE_H
#include <deque>
#include <memory_resource>

#include "Node.h"

/**
 * @namespace Grafcet
 * @brief Contient les classes et fonctions nécessaires pour générer et parcourir le Grafcet
 */
namespace Grafcet {
    /** @class StateMachine
     * @brief La machine à état permettant de parcourir le grafcet
     */
    class StateMachine {
    public:
        /// Constructeur par défaut de la machine à état
        StateMachine() = default;
        /// Constructeur de la machine à état avec un noeud de départ
        explicit StateMachine(Node *startingNode) : startingNode(startingNode) {}

        /**
         * @brief Assigne le noeud de départ du grafcet
         * @param startingNode
         */
        void setStartingNode(Node *startingNode) {this->startingNode = startingNode;}

        /**
         * @brief Parcours le grafcet en executant les actions
         * Utilise une queue pour garder en mémoire les noeuds actifs.
         * Si ces noeuds sont des actions ; la réaliser sinon évaluer
         * la transition
         */
        void execute();
    protected:
        /// Le noeud de départ
        Node* startingNode = nullptr;
        std::deque<Node*> activeNodes = {};
    };
}
#endif //TEAM2026_STATEMACHINE_H
