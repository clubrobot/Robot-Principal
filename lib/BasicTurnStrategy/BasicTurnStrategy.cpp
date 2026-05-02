//
// Created by gae on 05/04/26.
//

#include "BasicTurnStrategy.h"

#include "mathutils.h"

void BasicTurnStrategy::computeVelSetpoints(float timestep) {
    float dang = getPosSetpoint().theta - getPosInput().theta;
    float obj;
    float kp = 3;
    if (fabs(dang) > ang_precision) {
        obj = saturate(kp * dang, -ang_max_speed, ang_max_speed);
    } else {
        obj = 0;
    }
    setVelSetpoints(0, obj);
}

bool BasicTurnStrategy::getPositionReached() {
    ang_goalReached = fabs(getPosSetpoint().theta - getPosInput().theta) < ang_precision;
    if (ang_goalReached) {
        //printf("%f %f %f\n", getPosInput().x, getPosInput().y, getPosInput().theta);
        printf("L'objectif a été atteint, BasicTurn::getPositionReached est ok\n");
    }
    return ang_goalReached;
}