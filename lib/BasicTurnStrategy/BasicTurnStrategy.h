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
/**
 * @class BasicTurnStrategy
 * @ingroup wheeledbase
 * @ingroup libs
 * @brief Stratégie de mouvement basique.
 *
 * Stratégie développée afin de faire tourner le robot pour régler le PID.
 */
class BasicTurnStrategy : public AbstractMoveStrategy {

public:
    virtual ~BasicTurnStrategy() = default;
    PID ang_pid = {};
    PID lin_pid = {};
protected:
    void computeVelSetpoints(float timestep) override;
    bool getPositionReached() override;
};

#endif //TEAM2026_BASICMOVESTRATEGY_H
