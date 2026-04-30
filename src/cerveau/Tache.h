//
// Created by awing on 28/04/2026.
//

#ifndef TEAM2026_TACHE_H
#define TEAM2026_TACHE_H


struct Position;

/**
 * @brief Types et variables utilisés pour décrire une tâche du cerveau.
 */
namespace Tache {

    /**
     * @brief Mode d'interprétation d'une variable.
     *
     * DELTA applique une variation, ABSOLUTE fixe une valeur absolue,
     * et IGNORE laisse la variable inchangée.
     */
    enum Mode {
        IGNORE,
        ABSOLUTE,
        DELTA,
    };
    typedef Mode Mode;

    /**
     * @brief Variable typée associée à un mode de mise à jour.
     *
     * @tparam T Type de la valeur stockée.
     */
    template<typename T>
    struct Variable {
        /// Mode d'application de la valeur.
        Mode mode = IGNORE;
        /// Valeur courante.
        T value{};
    };

    /**
     * @brief Ensemble des variables pilotées par une tâche.
     */
    struct Tache {
        /// Variables du wheeled base.
        Variable<int> wb_x;
        Variable<int> wb_y;
        Variable<float> wb_theta;
        Variable<float> wb_maxLinVel;
        Variable<float> wb_maxAngVel;

        /// Variables liées à la pince et à l'ascenseur.
        Variable<float> elevator_height; ///en degré
        Variable<bool> clamp_open;
        Variable<bool> clamp_spread;
        Variable<bool> clamp_getColor;
        Variable<bool[4]> clamp_rotate;

        /// Specific actions
        Variable<bool> clamp_conditionalRotate;
    };
    typedef Tache Tache;
}
#endif //TEAM2026_TACHE_H
