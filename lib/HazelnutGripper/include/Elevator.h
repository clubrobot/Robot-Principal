
//
// Created by Romain Pouvreau on 08/03/2026.
//

#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "DifferentialController.h"

namespace HazelnutGripper
{
    /**
     * @class AbstractAbsoluteEncoder
     * @brief Interface pour un encodeur de position absolue.
     * * Cette classe définit le contrat pour tout capteur capable de fournir
     * * une position angulaire absolue.
     */
    class AbstractAbsoluteEncoder
    {
    public:
        virtual ~AbstractAbsoluteEncoder() = default;

        /**
         * @brief Récupère la position angulaire actuelle.
         * @return Angle mesuré en degrés (deg).
         */
        virtual float getAngle() = 0;

        /**
         * @brief Initialise le matériel de l'encodeur.
         */
        virtual void init() = 0;
    };

    /**
     * @namespace Elevator
     * @brief Namespace gérant l'asservissement en position de l'ascenseur.
     * * L'Elevator coordonne un moteur et un encodeur via un correcteur PID
     * pour atteindre et maintenir une position angulaire précise.
     */
    namespace Elevator
    {
        static AbstractMotor* m_motor = nullptr;            ///< Pointeur vers le moteur asservi.
        static AbstractAbsoluteEncoder* m_encoder = nullptr; ///< Pointeur vers l'encodeur de retour.

        static float m_angle = 0.0f; ///< Consigne de position angulaire (Setpoint) en degrés.

        static PID* m_pid = nullptr;    ///< Correcteur PID utilisé pour le calcul de la vitesse.


        /**
         * @brief Initialise les périphériques de l'ascenseur.
         * * Lie le moteur et l'encodeur à la classe et calibre la position
         * cible initiale sur la position actuelle de l'ascenseur.
         * * @param motor Référence vers le driver du moteur.
         * @param encoder Référence vers le capteur de position.
         */
        void init(AbstractMotor* motor, AbstractAbsoluteEncoder* encoder);

        /**
         * @brief Définit la position cible à atteindre.
         * @param angle Position souhaitée en degrés (deg).
         */
        inline void setAngle(float angle) { m_angle = angle; }

        /**
         * @brief Tâche de calcul de l'asservissement (Boucle de contrôle).
         * * Lit l'encodeur, calcule l'erreur, applique le PID et commande le moteur.
         * Cette méthode est conçue pour être lancée comme une tâche FreeRTOS.
         * * @param pvParameters Paramètres de tâche (non utilisés, typiquement NULL).
         */
        [[noreturn]] void task(void *pvParameters);

        /**
         * @brief Configure le correcteur PID à utiliser pour l'asservissement.
         * @param pid Référence vers l'objet PID configuré.
         */
        inline void setPID(PID& pid) { m_pid = &pid; }

        inline float getAngle() {
            return m_encoder->getAngle();
        }

    };
}

#endif // ELEVATOR_H