//
// Created by awing on 21/11/25.
//

#include "PositionController.h"
#include "DCMotor.h"
#include "VelocityController.h"
#include "PositionController.h"

#ifndef TEAM2026_BASICTURNSTRATEGY_H
#define TEAM2026_BASICTURNSTRATEGY_H

/*extern DCMotorsDriver driver;
extern DCMotor leftWheel;
extern DCMotor rightWheel;
extern VelocityController velocityControl;
extern PositionController positionControl;*/

class BasicTurnStrategy : public AbstractMoveStrategy {
    /**
     * @brief Stratégie de mouvement basique.
     *
     * Stratégie développée afin de faire tourner le robot pour régler le PID.
     */
public:
    float ang_precision;
    float ang_max_speed;
    float ang_slowing_distance;
    bool ang_goalReached;
protected:
    void computeVelSetpoints(float timestep) override;
    bool getPositionReached() override;
};

#endif //TEAM2026_BASICMOVESTRATEGY_H
