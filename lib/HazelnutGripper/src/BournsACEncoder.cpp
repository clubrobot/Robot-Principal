//
// Created by Romain Pouvreau on 08/03/2026.
//

#include "BournsACEncoder.h"

namespace HazelnutGripper
{
    BournsACEncoder::BournsACEncoder(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4, uint8_t pin5, uint8_t pin6, uint8_t pin7, uint8_t pin8)
    {
        this->m_pins[0] = pin1;
        this->m_pins[1] = pin2;
        this->m_pins[2] = pin3;
        this->m_pins[3] = pin4;
        this->m_pins[4] = pin5;
        this->m_pins[5] = pin6;
        this->m_pins[6] = pin7;
        this->m_pins[7] = pin8;
    }

    void BournsACEncoder::init()
    {
        for (int i = 0; i < 8; i++)
        {
            pinMode(this->m_pins[i], INPUT_PULLUP);
        }
    }

    uint8_t BournsACEncoder::binToDec(uint8_t bits[8])
    {
        int val = 0;

        for(int i = 0; i < 8; i++) {
            val = (val << 1) | bits[i];
        }

        return val;
    }

    float BournsACEncoder::getAngle()
    {
        uint8_t bits[8];

        for (int i = 0; i < 8; i++)
        {
            bits[i] = digitalRead(this->m_pins[i]);
        }

        if (conversion_table[binToDec(bits)] == -1)
        {
            return -1;
        }

        return conversion_table[binToDec(bits)] * step_angle;
    }
}