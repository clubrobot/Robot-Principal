//
// Created by awing on 21/11/25.
//

#include "mathutils.h"
#include "BasicMoveStrategy.h"


void BasicMoveStrategy::computeVelSetpoints(float timestep) {
    const Position setPoint = getPosSetpoint();
    const Position pos = getPosInput();
    const float dtheta = setPoint.theta - pos.theta;
    const float dx = setPoint.x - pos.x;
    const float dy = setPoint.y - pos.y;
    const float drho = dx * cos(theta_init) + dy * sin(theta_init);
    const float linObj = fabs(drho) > getLinPosThreshold() ? saturate(getLinVelKp() * drho, -getLinVelMax(), getLinVelMax()) : 0;
    const float angObj = fabs(dtheta) > getAngPosThreshold() ? saturate(getAngVelKp() * dtheta, -getAngVelMax(), getAngVelMax()) : 0;
    setVelSetpoints(linObj, angObj); //vitesse roue, et vitesse angulaire
}

bool BasicMoveStrategy::getPositionReached() {
    const Position setPoint = getPosSetpoint();
    const Position pos = getPosInput();
    const float dtheta = setPoint.theta - pos.theta;
    const float dx = setPoint.x - pos.x;
    const float dy = setPoint.y - pos.y;
    const float drho = dx * cos(theta_init) + dy * sin(theta_init);
    return fabs(drho) < getLinPosThreshold() && fabs(dtheta) < getAngPosThreshold();
}