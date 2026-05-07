//
// Created by awing on 28/04/2026.
//

#ifndef TEAM2026_TACHE_H
#define TEAM2026_TACHE_H
#include <string>


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

        bool operator==(const Variable& v) const {
            return mode == v.mode && value == v.value;
        }
    };

    /**
     * @brief Ensemble des variables pilotées par une tâche.
     */
    struct s_Tache {
        int index = -1;
        Variable<String> label;

        int operator+(const int n) const {
            return index + n;
        }

        int operator-(const int n) const {
            return index - n;
        }

        bool operator==(const s_Tache& t) const {
            return index == t.index && label == t.label;
        }

        ///goto
        Variable<String> goto_label;
        Variable<int> goto_offset;

        /// Variables du wheeled base.
        Variable<int> wb_x;
        Variable<int> wb_y;
        Variable<float> wb_theta;
        Variable<bool> wb_blocking;
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
    typedef s_Tache Tache;
}

template<>
struct std::hash<Tache::Tache> {
    size_t operator()(const Tache::Tache& t) const noexcept {
        return hash<int>()(t.index) ^ hash<std::string>()(t.label.value.c_str());
    }
};

template<>
struct std::hash<String>{
    size_t operator()(const String& s) const noexcept {
        return hash<std::string>()(s.c_str());
    }
};
#endif //TEAM2026_TACHE_H
