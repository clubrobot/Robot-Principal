//
// Created by awing on 21/11/25.
//

#include "BasicMoveStrategy.h"

#include "../mathutils/mathutils.h"
#include "../Teleplot/Teleplot_client.h"

float angle_init = 0;

void BasicMoveStrategy::computeVelSetpoints(float timestep) {


    float dang = -getPosInput().theta;
    teleplot.add_variable_float_2decimal("dang", dang);
    float obja;
    float akp = 1;
    if (fabs(dang) > 0.3) {
        obja = saturate(akp * dang, -PI/3, PI/3);
    } else {
        obja = 0;
    }



    float dx = getPosSetpoint().x - getPosInput().x;
    float kp = 1;
    float obj = fabs(dx) > x_precision ? saturate(dx * kp, -x_max_speed, x_max_speed) : 0;
    teleplot.add_variable_float_2decimal("diff", getPosInput().theta - angle_init);
    teleplot.add_variable_float_2decimal("angl",anglToVitAngl(angle_init, timestep));
    float correction_angle = saturate( 0.2 *  anglToVitAngl(angle_init, timestep), -PI/3, PI/3 );
    setVelSetpoints(obj, obja); //vitesse roue, et vitesse angulaire
    float angle_init = getPosInput().theta;
}

bool BasicMoveStrategy::getPositionReached() {
    x_goalReached = fabs(getPosSetpoint().x - getPosInput().x) < x_precision;
    if (x_goalReached) {
        //printf("%f %f %f\n", getPosInput().x, getPosInput().y, getPosInput().theta);
        //printf("L'objectif a été atteint, BasicMove::getPositionReached est ok\n");
    }
    return x_goalReached;
}

float BasicMoveStrategy::anglToVitAngl(float angle_init, float timestep) {
    float angle_now = getPosInput().theta;
    return (angle_now - angle_init) / timestep;
}