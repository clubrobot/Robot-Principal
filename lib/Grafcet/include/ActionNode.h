//
// Created by awing on 09/05/2026.
//
/**
 * @file ActionNode.h
 * @ingroup grafcet
 * @brief Un noeud d'action du grafcet, permettant de réaliser des actions de front montant
 */

#ifndef TEAM2026_ACTIONNODE_H
#define TEAM2026_ACTIONNODE_H
#include <functional>

#include "Node.h"

namespace Grafcet {
    /**
     * @class ActionNode
     * @brief Représente un noeud d'action dans le grafcet
     * Les noeuds d'action n'exécute qu'une seule fois leur opération, à l'activation (front montant) car
     * on assume que les actions réalisées dans le noeud sont non bloquantes. Une action bloquante dans
     * le noeud empêchera le graphe d'exécuter les noeuds voisins.
     *
     * Si synchronize == true, le noeud attend que toutes ses transitions enfants soient validée avant
     * de transitionner.
     */
    class ActionNode : public Node {
    public:
        /**
         * @brief Un noeud d'action est considéré comme activé si il est actif
         * @return true si actif
         */
        bool enabled() override {return active;}

        /**
         * @brief execute l'action personnalisée du noeud lors de son activation
         */
        void action() override {
            if (!active) {
                actionFunction();
                active = true;
            }
        }
        /// std::function pointant vers l'action à réaliser
        std::function<void()> actionFunction = nullptr;
    };
}
#endif //TEAM2026_ACTIONNODE_H
