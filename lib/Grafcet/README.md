<!--! @page libgrafcet libgrafcet -->
<!--! @ingroup grafcet -->
Copyright (C) 2026 Club Robot INSA Rennes This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, version 3. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details. You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.

Introduction
============

Cette librairie permet de créer et d'exécuter des pseudo-GRAFCETS. Il est à noter que cette librairie ne se veut pas conforme à la norme, mais seulement inspirée par celle-ci. Elle est donc plus simple, comporte moins de fonctionnalités et est plus limitée.

Compilation
============

Pour compiler la librairie, vous aurez besoin de CMake, d'un compilateur C++ et de la libc.

~~~~~~~~~~~~bash
cmake -B build
cd build
make
~~~~~~~~~~~~

Utilisation
============

Pour utiliser cette librairie, il vous faut créer une machine à états qui va lire ce grafcet, et lui passer le premier noeud du graphe.

~~~~~~~~~~~~c++
auto startingNode = Grafcet::ActionNode();
auto machine = Grafcet::StateMachine(*startingNode);
// ou alors
auto machine = Grafcet::StateMachine();
machine.setStartingNode(*startingNode);


/*  Une fois la machine créée, vous pouvez l'exécuter en appelant la méthode `execute()`. 
 *  Il faut maintenant définir le noeud.
 */
startingNode.actionFunction = []() {
    /* Code à exécuter pour ce noeud
     * vous pouvez également utiliser la capture de variables locales
     * ou bien une fonction nommée
     */
};

/*  Ensuite, vous pouvez lui ajouter des enfants.
 *  NB: Ajouter des actionNode enfants à un actionNode n'est pas supporté et provoquera
 *  un blocage silencieux du grafcet.
 */

auto t1 = Grafcet::Transition();
startingNode.addChild(t1);

/*  Vous pouvez maintenant définir la transition.
 *  NB: là où enchainer deux actionNode est impossible, enchainer deux transition est possible.
 */

t1.condition = [] {
    /* Code à exécuter pour cette transition
     * doit retourner un booléen
     */
}

~~~~~~~~~~~~
Les noeuds peuvent être déclaré synchronisant ou non.
 * Un actionNode synchronisant attend que TOUTES ses transitions enfants soient validées avant de transitionner vers le noeud suivant. Un actionNode non synchronisant ne nécessite qu'une seule transition validée pour transitionner.
 *  Une transition synchronisante attend que TOUTES ses noeuds parents soient activés avant de pouvoir évaluer sa condition. Une transition non synchronisante ne nécessite qu'un seul parent activé pour pouvoir évaluer sa condition.

