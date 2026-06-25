//
// Created by awing on 09/05/2026.
//
/**
 * @file Transition.h
 * @ingroup grafcet
 * @brief Un noeud de transition du grafcet permettant d'évaluer la condition de passage d'un noeud d'action à un autre
 */

#ifndef TEAM2026_TRANSITION_H
#define TEAM2026_TRANSITION_H
#include <functional>

#include "Node.h"
namespace Grafcet {
    /**
     * @class Transition
     * @brief Représente une transition dans le grafcet
     * Les noeuds de transition présente une fonction personnalisée `condition` qui est définie
     * par l'utilisateur. Une transition est activé si celle-ci est vrai et si au moins un de
     * ses parents est activé.
     *
     * Si synchronize == true, la transition attend que tout ses parents soit activés avant de
     * valider sa condition.
     */
    class Transition : public Node {
    public:
        Transition() {
            isTransition = true;
        }

        /**
         * @brief Les transitions n'ont pas d'actions
         */
        void action() override {}

        /**
         * @brief Vérifie si la transition est activé
         * Vérifie si la transition est activé en vérifiant l'état de ses parents
         * et en évaluant la fonction personnalisée passée
         * @return true si la transition est activé, false sinon
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
        /// std::function pointant vers la fonction à évaluer pour vérifier la condition de la transition
        std::function<bool()> condition = {};
    };
}
#endif //TEAM2026_TRANSITION_H
