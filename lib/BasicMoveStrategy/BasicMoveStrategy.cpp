//
// Created by awing on 21/11/25.
//

#include "BasicMoveStrategy.h"

float angle_init = 0;

void BasicMoveStrategy::computeVelSetpoints(float timestep) {
    float dx = getPosSetpoint().x - getPosInput().x;
    float obj;

    if (dx > 0) {
        obj = 150;  // x_max_speed
    } else {
        obj = -150;
    }
    if (fabs(dx) < 15){ // slowing_distance
        obj = x_max_speed * fabs(dx) / 15;
        obj = (dx > 0) ? obj : -obj;
    } else if (fabs(dx) < getPosSetpoint().x) {
        obj = 0;
    }

    float correction_angle = -anglToVitAngl(angle_init, timestep);

    Serial.print("Angle i - 1: ");
    Serial.println(angle_init);
    Serial.print("Le delta theta, l'angle a corriger:");
    Serial.println(correction_angle);
    Serial.print("__________________________________________\n"); 

    //setVelSetpoints(obj, correction_angle); //vitesse roue, et vitesse angulaire cad
    setVelSetpoints(obj, 0); //vitesse roue, et vitesse angulaire cad 

    float angle_init = getPosInput().theta;
}

bool BasicMoveStrategy::getPositionReached() {
    return (fabs(getPosSetpoint().x - getPosInput().x) < x_precision);
}

float BasicMoveStrategy::anglToVitAngl(float angle_init, float timestep) {
    float angle_now = getPosInput().theta;

    Serial.print("Angle i: ");
    Serial.println(angle_now);

    return (angle_now - angle_init) / timestep;
}