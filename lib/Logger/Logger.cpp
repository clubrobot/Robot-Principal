//
// Created by boris on 27/01/2025.
//

#include "Logger.h"
#include <cstdarg>

// Definitions of static members
LiquidCrystal* Logger::_lcdOutput = nullptr;
char Logger::_lcdBuffer[4][21] = {{0}};
uint8_t Logger::_lcdCursor = 0;


Logger::Logger(const char* name) {
    strncpy(_name, name, MAX_NAME);
}

int Logger::log(uint8_t level, const char* format, ...) {
    va_list args;
    int nbcharprinted;
    va_start(args, format);
    nbcharprinted = log_static(level, _name, format, args);
    va_end(args);
    return nbcharprinted;
}

int Logger::log_static(uint8_t level,char* name, const char* format, va_list args) {

    switch (level) {
    case ERROR_LEVEL:
        printf(COLOR_RED);
        //if (_lcdOutput != nullptr) {
        //    va_list args_copy;
        //    va_copy(args_copy, args);
        //    vsnprintf(_lcdBuffer[_lcdCursor], 20, format, args_copy);
        //    va_end(args_copy);
        //    _lcdOutput->setCursor(0, _lcdCursor);
        //    constexpr char tmp[20]  = {0};
        //    _lcdOutput->print(tmp);
        //    _lcdOutput->setCursor(0, _lcdCursor);
        //    _lcdOutput->print(_lcdBuffer[_lcdCursor]);
        //}
        //_lcdCursor = (_lcdCursor + 1) % 4;
        break;
    case WARNING_LEVEL:
        printf(COLOR_YELLOW);
       //     if (_lcdOutput != nullptr) {
       //         va_list args_copy;
       //         va_copy(args_copy, args);
       //         vsnprintf(_lcdBuffer[_lcdCursor], 20, format, args_copy);
       //         va_end(args_copy);
       //         _lcdOutput->setCursor(0, _lcdCursor);
       //         constexpr char tmp[20]  = {0};
       //         _lcdOutput->print(tmp);
       //         _lcdOutput->setCursor(0, _lcdCursor);
       //         _lcdOutput->print(_lcdBuffer[_lcdCursor]);
       //     }
       //     _lcdCursor = (_lcdCursor + 1) % 4;
        break;
    case INFO_LEVEL:
        printf(COLOR_CYAN);
        break;
    case GOOD_LEVEL:
        printf(COLOR_GREEN);
        break;
    case SCREEN_LEVEL:
        if (_lcdOutput != nullptr) {
            va_list args_copy;
            va_copy(args_copy, args);
            vsnprintf(_lcdBuffer[_lcdCursor], 21, format, args_copy);
            va_end(args_copy);
            _lcdOutput->setCursor(0, _lcdCursor);
            constexpr char tmp[20]  = {0};
            _lcdOutput->print(tmp);
            _lcdOutput->setCursor(0, _lcdCursor);
            _lcdOutput->print(_lcdBuffer[_lcdCursor]);
        }
        _lcdCursor = (_lcdCursor + 1) % 4;
        return 0;
    default:
        printf(COLOR_NORMAL);
        break;
    }
    printf("[%s] ", name);
    va_list args_copy;
    va_copy(args_copy, args);
    int nbcharprinted = vprintf(format, args_copy);
    va_end(args_copy);
    printf(COLOR_NORMAL);
    return nbcharprinted;
}

void Logger::sameLine(const char * str) {
    if (_lcdOutput != nullptr) _lcdOutput->print(str);
}