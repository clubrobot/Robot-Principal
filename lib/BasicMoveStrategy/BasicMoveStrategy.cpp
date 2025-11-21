//
// Created by awing on 21/11/25.
//

#include "BasicMoveStrategy.h"

void BasicMoveStrategy::computeVelSetpoints(float timestep) {
    float dx = getPosSetpoint().x - getPosInput().x;
    float obj;
    if (dx > 0) {
        obj = x_max_speed;
    } else {
        obj = -x_max_speed;
    }
    if (fabs(dx) < slowing_distance){
        obj = x_max_speed * fabs(dx) / slowing_distance;
        obj = (dx > 0) ? obj : -obj;
    } else if (fabs(dx) < getPosSetpoint().x) {
        obj = 0;
    }
    setVelSetpoints(obj, 0);
}

bool BasicMoveStrategy::getPositionReached() {
    return (fabs(getPosSetpoint().x - getPosInput().x) < x_precision);
}