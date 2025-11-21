#include "PositionController.h"

namespace PositionController{
    bool getPositionReached(const PositionController* positionController){
        if (positionController->m_moveStrategy != nullptr)
            return positionController->m_moveStrategy->getPositionReached();
        return false;
    }

    void setMoveStrategy(PositionController* positionController, AbstractMoveStrategy* moveStrategy){
        positionController->m_moveStrategy = moveStrategy;
        positionController->m_moveStrategy->m_context = positionController;
    }

    void process(PositionController* positionController){
        float timestep = positionController->clock->getElapsedTime();
        if (positionController->m_moveStrategy != nullptr)
            positionController->m_moveStrategy->computeVelSetpoints(timestep);
        positionController->clock->restart();
    }
    
    void enable(PositionController* positionController){
        positionController->enabled = true; positionController->clock->restart();
    }
    void disable(PositionController* positionController){
        positionController->enabled = false;
    }

    // Implémentations déplacées depuis le header
    void setPosInput(PositionController* positionController, Position posInput){
        positionController->m_posInput = posInput;
    }

    void setPosSetpoint(PositionController* positionController, Position posSetpoint){
        positionController->m_posSetpoint = posSetpoint;
    }

    void setThetaSetPoint(PositionController* positionController, float theta){
        positionController->m_posSetpoint.theta = theta;
    }

    float getLinVelSetpoint(const PositionController* positionController){
        return positionController->m_linVelSetpoint;
    }

    float getAngVelSetpoint(const PositionController* positionController){
        return positionController->m_angVelSetpoint;
    }

    void setVelTunings(PositionController* positionController, float linVelKp, float angVelKp) {
        positionController->m_linVelKp = linVelKp;
        positionController->m_angVelKp = angVelKp;
    }

    void setVelLimits(PositionController* positionController, float linVelMax, float angVelMax){
        positionController->m_linVelMax = linVelMax;
        positionController->m_angVelMax = angVelMax;
    }

    void setPosThresholds(PositionController* positionController, float linPosThreshold, float angPosThreshold) {
        positionController->m_linPosThreshold = linPosThreshold;
        positionController->m_angPosThreshold = angPosThreshold;
    }

    float getLinVelKp(const PositionController* positionController){
        return positionController->m_linVelKp;
    }

    float getAngVelKp(const PositionController* positionController){
        return positionController->m_angVelKp;
    }

    float getLinVelMax(const PositionController* positionController){
        return positionController->m_linVelMax;
    }

    float getAngVelMax(const PositionController* positionController){
        return positionController->m_angVelMax;
    }

    float getLinPosThreshold(const PositionController* positionController){
        return positionController->m_linPosThreshold;
    }

    float getAngPosThreshold(const PositionController* positionController){
        return positionController->m_angPosThreshold;
    }

} // namespace PositionController

