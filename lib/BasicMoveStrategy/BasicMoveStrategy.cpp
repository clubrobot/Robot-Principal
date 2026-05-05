//
// Created by awing on 21/11/25.
//

#include "mathutils.h"
#include "BasicMoveStrategy.h"

#include "Teleplot.h"


void BasicMoveStrategy::computeVelSetpoints(float timestep) {
    const Position setPoint = getPosSetpoint();
    const Position pos = getPosInput();
    const float dx = setPoint.x - pos.x;
    const float dy = setPoint.y - pos.y;
    const float drho = dx * cos(pos.theta) + dy * sin(pos.theta);
    const float dist = sqrt(dx*dx + dy*dy);
    if (distanceInit == 0) {
        distanceInit = dist;
    }
    const float tauxDist = dist / distanceInit;
    const float sigmoid = 1/(1 + exp(- 50 * (tauxDist - 0.15f)));
    const float factor = tauxDist * sigmoid;
    const float dtheta = (atan2(dy, dx) + pos.theta) * factor + (setPoint.theta - pos.theta) * (1 - factor);
    const float linObj = fabs(drho) > getLinPosThreshold() ? saturate(getLinVelKp() * drho, -getLinVelMax(), getLinVelMax()) : 0;
    const float angObj = fabs(dtheta) > getAngPosThreshold() ? saturate(getAngVelKp() * dtheta, -getAngVelMax(), getAngVelMax()) : 0;
    teleplot.add_variable_float_2decimal("dx", dx);
    teleplot.add_variable_float_2decimal("dy", dy);
    teleplot.add_variable_float_2decimal("drho", drho);
    teleplot.add_variable_float_2decimal("dtheta", dtheta);
    teleplot.add_variable_float_2decimal("linObj", linObj);
    teleplot.add_variable_float_2decimal("angObj", angObj);
    teleplot.add_variable_float_2decimal("dist", dist);
    teleplot.add_variable_float_2decimal("tauxDist", tauxDist);
    teleplot.add_variable_float_2decimal("sigmoid", sigmoid);

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