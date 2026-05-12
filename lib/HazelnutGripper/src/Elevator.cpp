//
// Created by Romain Pouvreau on 14/04/2026.
//

#include "Elevator.h"

namespace HazelnutGripper
{

    void Elevator::init(AbstractMotor* motor, AbstractAbsoluteEncoder* encoder)
    {
        m_motor = motor;
        m_encoder = encoder;
        m_encoder->init();

        // Sécurité : on initialise la cible sur la position actuelle
        m_angle = m_encoder->getAngle();
    }


    void Elevator::task(void *pvParameters)
    {
        // Initialisation du temps pour le calcul du timestep
        uint32_t lastTime = millis();

        while (true)
        {
            uint32_t currentTime = millis();
            float timestep = (currentTime - lastTime) / 1000.0f;

            if (timestep <= 0.0f) {
                timestep = 0.001f;
            }

            // Lecture de la position actuelle via l'encodeur
             m_currentAngle = m_encoder->getAngle();
            printf("Current Angle: %f\n", m_currentAngle);

            // Calcul de la commande via le PID
            float command = 0.0f;
            if (m_pid != nullptr)
            {
                command = m_pid->compute(m_angle, m_currentAngle, timestep);
            }

            //m_motor->setVelocity(command);

            // Mise à jour du temps pour la prochaine itération
            lastTime = currentTime;

            vTaskDelay(pdMS_TO_TICKS(10));
        }
    }
}