//
// Created by boris on 30/10/2024.
//
/**
 * @file SensorsThread.h
 * @ingroup sensors
 * @ingroup core
 * @brief Contient les fonctions et variables nécessaires pour gérer le thread des capteurs.
 */

#ifndef SENSORS_THREAD_H
#define SENSORS_THREAD_H

#include <FreeRTOS.h>

#include "include/SensorArray.h"

namespace SensorsThread
{

    void Init();


    inline i2c_t i2c2 = {.sda = PB_11, .scl = PB_10, .isMaster = 1, .generalCall = false, .NoStretchMode = false};
    inline SensorArray sensors = SensorArray(&i2c2, PE14, PE13, PE15);;

    void Thread(void *pvParameters);

}

#endif //SENSORS_THREAD_H
