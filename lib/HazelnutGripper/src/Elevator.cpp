//
// Created by Romain Pouvreau on 14/04/2026.
//

#include "Elevator.h"

namespace HazelnutGripper
{
    void Elevator::task(void *pvParameters) const
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
            float currentAngle = m_encoder.getAngle();

            // Calcul de la commande via le PID
            float command = 0.0f;
            if (m_pid != nullptr)
            {
                command = m_pid->compute(m_angle, currentAngle, timestep);
            }

            m_motor.setVelocity(command);

            // Mise à jour du temps pour la prochaine itération
            lastTime = currentTime;

            vTaskDelay(pdMS_TO_TICKS(10));
        }
    }
}