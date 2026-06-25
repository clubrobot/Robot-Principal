//
// Created by boris on 27/01/2025.
//
/**
 * @file Logger.h
 * @ingroup ihm
 * @ingroup libs
 * @brief Un logger qui permet d'avoir une belle sortie console
 */
#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>
#include "coloring.h"
#if LCD_OUTPUT
#include "LiquidCrystal.h"
#include <string>
#endif

/**
 *
 * @defgroup log_levels Niveau de logs
 * @ingroup globals
 * @brief les niveaux de logs disponibles
 * @{
 */
//TODO: (2026-06-25) utiliser un enum
#define MAX_NAME 50
#define ERROR_LEVEL 3
#define WARNING_LEVEL 2
#define GOOD_LEVEL 1
#define INFO_LEVEL 0
#define SCREEN_LEVEL 10
///@}
#undef Error_Handler
#define Error_Handler() \
while (1) {\
printf("ERREUR MAJEURE dans %s:%d:%s \n", __FILE__, __LINE__,__FUNCTION__);\
digitalWrite(LED_RED, HIGH);\
delay(500);\
digitalWrite(LED_RED, LOW);\
delay(500);\
}

/**
 * @class Logger
 * @brief Log pour la sortie console avec des couleurs et éventuellement la sortie LCD
 */
class Logger {
public:
    /**
     * @brief Constructeur du logger.
     * @param name Nom du logger (sera affiché dans les logs).
     */
    Logger(const char* name);

    /**
     * @brief affiche un message sur la sortie
     * @param level Niveau de log (INFO, WARNING...)
     * @param format Le message avec les specifiers de format au format printf
     * @param ... Les valeurs à passer à printf
     * @return Le nombre de caractères imprimés
     */
    int log(uint8_t level, const char* format, ...);

    /**
     * @brief Attache un écran LCD
     * @param lcd L'écran à attacher
     */
    static void setLcdOutput(LiquidCrystal &lcd) {
        _lcdOutput = &lcd;
    }

    /**
     * @brief Ajoute du texte sur la même ligne
     * @param str Le texte à ajouter
     */
    static void sameLine(const char* str);
private:
    ///@brief Nom du logger
    char _name[50];
    ///@brief Fonction statique qui fait le log
    static int log_static(uint8_t level,char* name, const char* format, va_list args);
    ///@brief Pointeur vers l'écran LCD (si utilisé)
    static LiquidCrystal* _lcdOutput;
    ///@brief Buffer pour l'écran LCD (4 lignes de 20 caractères)
    static char _lcdBuffer[4][21];
    ///@brief Curseur pour l'écran LCD (ligne actuelle)
    static uint8_t _lcdCursor;
}; // Logger

#endif //LOGGER_H
