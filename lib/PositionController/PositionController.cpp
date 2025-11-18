#include <Arduino.h>
#include <EEPROM.h>

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
}

void PositionControllerOld::process(float timestep)
{
	if (m_moveStrategy != 0)
		m_moveStrategy->computeVelSetpoints(timestep);
}

void PositionControllerOld::onProcessEnabling()
{
	//m_posSetpoint = m_posInput;
}


