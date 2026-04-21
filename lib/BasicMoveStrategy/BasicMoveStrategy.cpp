//
// Created by awing on 21/11/25.
//

#include "BasicMoveStrategy.h"

#include "../Logger/Logger.h"

float angle_init = 0;
Logger MoveStrategyLog = Logger("MoveStrategyLog");

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
    float correction_angle = -anglToVitAngl(angle_init, timestep);
    setVelSetpoints(obj, correction_angle); //vitesse roue, et vitesse angulaire
    float angle_init = getPosInput().theta;
}

bool BasicMoveStrategy::getPositionReached() {
    x_goalReached = fabs(getPosSetpoint().x - getPosInput().x) < x_precision;
    if (x_goalReached) {
        //MoveStrategyLog.log(INFO_LEVEL, "%f %f %f\n", getPosInput().x, getPosInput().y, getPosInput().theta);
        //MoveStrategyLog.log(INFO_LEVEL, "%f %f %f\n", getPosSetpoint().x, getPosSetpoint().y, getPosSetpoint().theta);
        //MoveStrategyLog.log(INFO_LEVEL, "L'objectif a été atteint, BasicMove::getPositionReached est ok\n");
    }
    return x_goalReached;
}

float BasicMoveStrategy::anglToVitAngl(float angle_init, float timestep) {
    float angle_now = getPosInput().theta;
    return (angle_now - angle_init) / timestep;
}