//
// Created by gae on 05/04/26.
//

#include "BasicTurnStrategy.h"

#include "mathutils.h"
#include "Teleplot.h"

void BasicTurnStrategy::computeVelSetpoints(float timestep) {
    const Position SetPoint = getPosSetpoint();
    const Position pos = getPosInput();
    const float dang = SetPoint.theta - pos.theta;
    const float dx = SetPoint.x - pos.x;
    const float dy = SetPoint.y - pos.y;
    const float drho = dx * cos(pos.theta) + dy * sin(pos.theta);
    const float angObj = fabs(dang) > getAngPosThreshold() ? saturate(getAngVelKp() * dang, -getAngVelMax(), getAngVelMax()) : 0;
    const float linObj = fabs(drho) > getLinPosThreshold() ? saturate(getLinVelKp() * drho, -getLinVelMax(), getLinVelMax()) : 0;
    setVelSetpoints(-linObj, -angObj);
}

bool BasicTurnStrategy::getPositionReached() {
    const Position pos = getPosInput();
    const Position setPoint = getPosSetpoint();
    return fabs(setPoint.theta - pos.theta) < getAngPosThreshold() &&
           (setPoint.x - pos.x) * cos(pos.theta) + (setPoint.y - pos.y) * sin(pos.theta) < getLinPosThreshold()
        ;
}