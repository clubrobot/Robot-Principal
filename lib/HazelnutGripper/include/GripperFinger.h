//
// Created by Romain Pouvreau on 14/04/2026.
//

#ifndef GRIPPERFINGER_H
#define GRIPPERFINGER_H

#include <Wire.h>

/**
 * @namespace HazelnutGripper
 * @brief Espace de noms regroupant les fonctionnalités de contrôle de la pince Baguette.
 */
namespace HazelnutGripper
{
    /**
     * @struct ColorData
     * @brief Structure regroupant les valeurs brutes du capteur de couleur TCS3472.
     */
    struct ColorData {
        uint16_t clear; ///< Luminosité totale (lux)
        uint16_t red;   ///< Composante Rouge
        uint16_t green; ///< Composante Verte
        uint16_t blue;  ///< Composante Bleue
    };

    /**
     * @enum OperationMode
     * @brief Modes de fonctionnement du capteur de couleur.
     */
    enum class OperationMode : uint8_t {
        Standby    = 0x01, ///< Capteur en sommeil (consommation réduite)
        SingleRead = 0x02, ///< Effectue une seule lecture puis repasse en Standby
        Continuous = 0x03  ///< Échantillonnage périodique automatique
    };

    /**
     * @class GripperFinger
     * @brief Driver pour le doigt de pince "Baguette" communiquant via I2C.
     * * Cette classe permet de piloter les LEDs, les servos et le moteur DC,
     * tout en récupérant l'état de santé du système et les données colorimétriques.
     */
    class GripperFinger
    {
    public:
        /**
         * @brief Constructeur de la classe GripperFinger.
         * @param address Adresse I2C de la pince (par défaut 0x24).
         * @param wire Instance du bus i2c.
         */
        GripperFinger(TwoWire* wire, uint8_t address = 0x24);

        /**
         * @brief Allume ou éteint la LED de statut (Jaune).
         * @param enable true pour allumer, false pour éteindre.
         */
        void enableStatusLed(bool enable);

        /**
         * @brief Allume ou éteint la LED d'action (Bleue).
         * @param enable true pour allumer, false pour éteindre.
         */
        void enableActionLed(bool enable);

        /**
         * @brief Définit l'angle d'un servomoteur.
         * @param servoIndex Index du servo (1 ou 2).
         * @param degrees Angle cible en degrés (0 à 180).
         */
        void setAngle(uint8_t servoIndex, uint8_t degrees);

        /**
         * @brief Lance l'ouverture de la pince.
         */
        void open();

        /**
         * @brief Lance la fermeture de la pince.
         */
        void close();

        /**
         * @brief Arrête immédiatement le moteur de la pince.
         */
        void stop();

        /**
         * @brief Vérifie si le moteur est actuellement alimenté.
         * @return true si le moteur tourne, false sinon.
         */
        bool isMoving();

        /**
         * @brief Vérifie si la pince a terminé son mouvement vers la cible.
         * @return true si la position cible est atteinte.
         */
        bool isTargetReached();

        /**
         * @brief Vérifie si le driver moteur est en état de faute.
         * @return true en cas d'erreur matérielle (ex: surintensité).
         */
        bool isFaulty();

        /**
         * @brief Définit le mode de lecture du capteur TCS3472.
         * @param mode Standby, SingleRead ou Continuous.
         */
        void setSensingMode(OperationMode mode);

        /**
         * @brief Indique si une nouvelle mesure de couleur a été effectuée.
         * @note Ce flag est automatiquement réinitialisé après l'appel à getColor().
         * @return true si une donnée fraîche est disponible.
         */
        bool hasNewColorData();

        /**
         * @brief Récupère l'ensemble des valeurs RGBC du capteur.
         * @return Une structure ColorData contenant les 4 canaux sur 16 bits.
         */
        ColorData getColor();

    private:
        uint8_t _addr;

        TwoWire* _wire;

        void _write8(uint8_t cmd, uint8_t value);
        uint8_t _read8(uint8_t cmd);
        uint16_t _read16(uint8_t cmd);

        /**
         * @enum Register
         * @brief Adresses internes des registres du STM32 (conformes à la documentation).
         */
        enum Register : uint8_t {
            REG_YELLOW_LED     = 0x01,
            REG_BLUE_LED       = 0x02,
            REG_SERVO_1_POS    = 0x03,
            REG_SERVO_2_POS    = 0x04,
            REG_MOTOR_TARGET   = 0x05,
            REG_MOTOR_STATUS   = 0x06,
            REG_COLOR_INT_TIME = 0x07,
            REG_COLOR_GAIN     = 0x08,
            REG_COLOR_STATUS   = 0x09,
            REG_COLOR_MODE     = 0x0A,
            REG_COLOR_C_HIGH   = 0x0B,
            REG_COLOR_R_HIGH   = 0x0D,
            REG_COLOR_G_HIGH   = 0x0F,
            REG_COLOR_B_HIGH   = 0x11
        };
    };
}
#endif //GRIPPERFINGER_H