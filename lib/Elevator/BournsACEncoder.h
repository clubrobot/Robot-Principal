//
// Created by Romain Pouvreau on 08/03/2026.
//

#ifndef BOURNSACENCODER_H
#define BOURNSACENCODER_H
#include "Elevator.h"

class BournsACEncoder : public AbstractAbsoluteEncoder
{
public:
    BournsACEncoder(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4, uint8_t pin5, uint8_t pin6, uint8_t pin7, uint8_t pin8);

    void init() override;

    /**
     * @brief Donne la valeur de la position anglulaire
     * @return -1 si il y a problème, sinon la valeur de l'angle
     */
    float getAngle() override;

protected:

    const float total_steps = 128;
    const float step_angle = 360 / total_steps; /*!< Nombre de degrés par pas */

    /**
     * Table de conversion entre la valeurs des pins et la position en pas (https://www.bourns.com/data/global/pdfs/ace.pdf)
     */
    const int conversion_table[255] = {-1,56,40,55,24,-1,39,52,8,57,-1,-1,23,-1,36,13,120,-1,41,54,-1,-1,-1,53,7,-1,-1,-1,20,19,125,18,104,105,-1,-1,25,106,38,-1,-1,58,-1,-1,-1,-1,37,14,119,118,-1,-1,-1,107,-1,-1,4,-1,3,-1,109,108,2,1,88,-1,89,-1,-1,-1,-1,51,9,10,90,-1,22,11,-1,12,-1,-1,42,43,-1,-1,-1,-1,-1,-1,-1,-1,21,-1,126,127,103,-1,102,-1,-1,-1,-1,-1,-1,-1,91,-1,-1,-1,-1,-1,116,117,-1,-1,115,-1,-1,-1,93,94,92,-1,114,95,113,0,72,71,-1,68,73,-1,-1,29,-1,70,-1,69,-1,-1,35,34,121,-1,122,-1,74,-1,-1,30,6,-1,123,-1,-1,-1,124,17,-1,-1,-1,67,26,-1,27,28,-1,59,-1,-1,-1,-1,-1,15,-1,-1,-1,-1,-1,-1,-1,-1,5,-1,-1,-1,110,-1,111,16,87,84,-1,45,86,85,-1,50,-1,-1,-1,46,-1,-1,-1,33,-1,83,-1,44,75,-1,-1,31,-1,-1,-1,-1,-1,-1,-1,32,100,61,101,66,-1,62,-1,49,99,60,-1,47,-1,-1,-1,48,77,82,78,65,76,63,-1,64,98,81,79,80,97,96,112};

    uint8_t m_pins[8]{};

    static uint8_t binToDec(uint8_t bits[8]);
};

#endif //BOURNSACENCODER_H