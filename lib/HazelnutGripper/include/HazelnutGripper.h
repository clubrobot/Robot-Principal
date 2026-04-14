//
// Created by Romain Pouvreau on 14/04/2026.
//

#ifndef HAZELNUTGRIPPER_H
#define HAZELNUTGRIPPER_H

#include "GripperFinger.h"

namespace HazelnutGripper
{
    inline TwoWire GripperWire(PC9, PA8);;
    /**
         * @class Gripper
         * @brief Classe de haut niveau pour piloter l'ensemble de la pince (4 doigts).
         */
    class Gripper
    {
    public:
        Gripper() = delete;

        /**
         * @brief Initialise les adresses I2C des 4 doigts.
         * Par défaut : 0x24, 0x25, 0x26, 0x27
         */
        static void init(uint8_t addr1 = 0x24, uint8_t addr2 = 0x25,
                         uint8_t addr3 = 0x26, uint8_t addr4 = 0x27);

        /**
         * @brief Ouvre les 4 doigts simultanément.
         */
        static void openAll();

        /**
         * @brief Ferme les 4 doigts simultanément.
         */
        static void closeAll();

        /**
         * @brief Définit l'angle du Servo 1 pour tous les doigts (rotation).
         * @param degrees Angle en degrés (0-180).
         */
        static void setRotationAll(uint8_t degrees);

        /**
         * @brief Écarte la pince en utilisant le servo 2 du doigt n°1.
         * @param degrees Angle d'écartement.
         */
        static void spreadFinger1(uint8_t degrees);

        /**
         * @brief Accès direct à un doigt spécifique si besoin.
         * @param index Numéro du doigt (0 à 3).
         */
        static GripperFinger& getFinger(uint8_t index);

    private:
        static GripperFinger _fingers[4];
    };
}

#endif //HAZELNUTGRIPPER_H