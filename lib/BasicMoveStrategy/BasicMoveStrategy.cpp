//
// Created by awing on 21/11/25.
//

#include "BasicMoveStrategy.h"

float angle_init = 0;

void BasicMoveStrategy::computeVelSetpoints(float timestep) {
    float dx = getPosSetpoint().x - getPosInput().x;
    float obj;
    if (dx > 0 && dx > x_slowing_distance) {
        obj = x_max_speed;  // 
    } else if (dx < 0 && fabs(dx) > x_slowing_distance) {
        obj = -x_max_speed;
    } else {
        obj = x_max_speed * fabs(dx) / x_slowing_distance;
        obj = (dx > 0) ? obj : -obj;
    }
    float correction_angle = -anglToVitAngl(timestep);
    setVelSetpoints(obj, correction_angle); //vitesse roue, et vitesse angulaire
}

bool BasicMoveStrategy::getPositionReached() {
    x_goalReached = fabs(getPosSetpoint().x - getPosInput().x) < x_precision;
    if (x_goalReached) {
        //printf("%f %f %f\n", getPosInput().x, getPosInput().y, getPosInput().theta);
        //printf("L'objectif a été atteint, BasicMove::getPositionReached est ok\n");
    }
    return x_goalReached;
}

float BasicMoveStrategy::anglToVitAngl(float timestep) {
    float angle_now = getPosInput().theta;
    return (angle_now - this->theta_init) / timestep;
}