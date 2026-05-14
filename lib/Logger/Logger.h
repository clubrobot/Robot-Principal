//
// Created by boris on 27/01/2025.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>
#include "coloring.h"
#if LCD_OUTPUT
#include "LiquidCrystal.h"
#include <string>
#endif

#define MAX_NAME 50
#define ERROR_LEVEL 3
#define WARNING_LEVEL 2
#define GOOD_LEVEL 1
#define INFO_LEVEL 0
#define SCREEN_LEVEL 10

#undef Error_Handler
#define Error_Handler() \
while (1) {\
printf("ERREUR MAJEURE dans %s:%d:%s \n", __FILE__, __LINE__,__FUNCTION__);\
digitalWrite(LED_RED, HIGH);\
delay(500);\
digitalWrite(LED_RED, LOW);\
delay(500);\
}

class Logger {
public:
    Logger(const char* name);
    int log(uint8_t level, const char* format, ...);
    static void setLcdOutput(LiquidCrystal &lcd) {
        _lcdOutput = &lcd;
    }
    static void sameLine(const char* str);
private:
    char _name[50];
    static int log_static(uint8_t level,char* name, const char* format, va_list args);
    static LiquidCrystal* _lcdOutput;
    static char _lcdBuffer[4][21];
    static uint8_t _lcdCursor;
}; // Logger

#endif //LOGGER_H
