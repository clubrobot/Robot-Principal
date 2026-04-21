//
// Created by gae on 05/04/26.
//

#include "BasicTurnStrategy.h"

void BasicTurnStrategy::computeVelSetpoints(float timestep) {
    float dang = getPosSetpoint().theta - getPosInput().theta;
    float obj;
    if (dang > 0 && dang > ang_slowing_distance) {
        obj = ang_max_speed; 
    } else if (dang < 0 && fabs(dang) > ang_slowing_distance) {
        obj = -ang_max_speed;
    } else { 
        obj = ang_max_speed * fabs(dang) / ang_slowing_distance;
        obj = (dang > 0) ? obj : -obj;
    } 
    setVelSetpoints(0, -obj);
}

bool BasicTurnStrategy::getPositionReached() {
    ang_goalReached = fabs(getPosSetpoint().theta - getPosInput().theta) < ang_precision;
    if (ang_goalReached) {
        printf("%f %f %f\n", getPosInput().x, getPosInput().y, getPosInput().theta);
        printf("L'objectif a été atteint, BasicTurn::getPositionReached est ok\n");
    }
    return ang_goalReached;
}