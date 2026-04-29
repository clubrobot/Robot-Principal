
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
     * @class Elevator
     * @brief Classe statique gérant l'asservissement en position de l'ascenseur.
     * * L'Elevator coordonne un moteur et un encodeur via un correcteur PID
     * pour atteindre et maintenir une position angulaire précise.
     */
    class Elevator
    {
    public:
        /** @brief Classe statique : l'instanciation est interdite. */
        Elevator() = delete;

        /**
         * @brief Initialise les périphériques de l'ascenseur.
         * * Lie le moteur et l'encodeur à la classe et calibre la position
         * cible initiale sur la position actuelle de l'ascenseur.
         * * @param motor Référence vers le driver du moteur.
         * @param encoder Référence vers le capteur de position.
         */
        static void init(AbstractMotor* motor, AbstractAbsoluteEncoder* encoder);

        /**
         * @brief Définit la position cible à atteindre.
         * @param angle Position souhaitée en degrés (deg).
         */
        static void setAngle(float angle) { m_angle = angle; }

        /**
         * @brief Tâche de calcul de l'asservissement (Boucle de contrôle).
         * * Lit l'encodeur, calcule l'erreur, applique le PID et commande le moteur.
         * Cette méthode est conçue pour être lancée comme une tâche FreeRTOS.
         * * @param pvParameters Paramètres de tâche (non utilisés, typiquement NULL).
         */
        static void task(void *pvParameters);

        /**
         * @brief Configure le correcteur PID à utiliser pour l'asservissement.
         * @param pid Référence vers l'objet PID configuré.
         */
        static void setPID(PID& pid) { m_pid = &pid; }

    protected:
        static AbstractMotor* m_motor;            ///< Pointeur vers le moteur asservi.
        static AbstractAbsoluteEncoder* m_encoder; ///< Pointeur vers l'encodeur de retour.

        static float m_angle; ///< Consigne de position angulaire (Setpoint) en degrés.

        static PID* m_pid;    ///< Correcteur PID utilisé pour le calcul de la vitesse.
    };
}

#endif // ELEVATOR_H