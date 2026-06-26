<!--! \page base_roulante Base Roulante -->
<!--! \ingroup wheeledbase -->
# PC, DC, VC, kézako ?
Dans cette section, nous allons aborder le schéma compliqué qu'entretiennent les différents composants de la base roulante du robot.
* **\ref PositionController (PC)** : Ce composant gère l'asservissement en position du robot.
* **\ref VelocityController (VC)** : Ce composant gère l'asservissement en vitesse du robot. Il hérite du plus simple **\ref DifferentialController (DC)** qui calcule la vitesse de rotation
des roues à partir de la sortie du **\ref PID**.
* **\ref AbstractMoveStrategy MoveStrategy** : Ce composant est responsable de la stratégie de mouvement du robot : à partir de la position actuelle, il va calculer la consigne en vitesse du robot.
* **\ref Odometry** : L'odométrie permet de déterminer la position du robot à partir de la vitesse des codeuses.
* Le VC et le PC sont tous deux des **\ref PeriodicProcess** : ils ont une fonction `PeriodicProcess::update()` qui est appelée tous les `PeriodicProcess::m_timestep` ms.
* **\ref Wheeledbase.h** : Ce fichier contient un certain nombre de fonctions auxiliaires se reposant sur les composants précédemment cités pour permettre de piloter le robot plus facilement.

# Et comment tout ça est relié ?
À chaque itération de la boucle de la base roulante, gardez en tête que ça ne se produit que s'il est possible de le faire, c'est-à-dire que le timestep du PeriodicProcess est écoulé.
Dans l'ordre, l'odométrie est mise à jour, ce qui permet de déterminer la position actuelle du robot. Ensuite, le PositionController appelle la stratégie de mouvement pour déterminer
la consigne en vitesse du robot. Il transmet ensuite cette consigne au VelocityController. Celui-ci applique des traitements (notamment des rampes) à la consigne de vitesse. Une fois que la
consigne est prête, le VelocityController va la transmettre au DifferentialController, qui va appliquer le PID et déterminer la vitesse de rotation de chaque roue. Enfin le DC va transmettre
ces consignes directement aux drivers.

Ce système permet à la fois une grande flexibilité (possibilité d'implémenter plusieurs MoveStrategy), mais aussi une grande robustesse. Toutefois, il est à noter qu'il y a beaucoup de constantes à
régler (constantes du PID, rayon des roues, écart entre les roues, etc.), et que les systèmes sont difficilement découplable, aussi, il faut s'y prendre à l'avance dans le réglage de ces constantes.

# Comment régler ces constantes alors ?
TODO