#include <Arduino.h>

#include "PositionController.h"


void PositionController::setMoveStrategy(AbstractMoveStrategy& moveStrategy)
{
	m_moveStrategy = &moveStrategy;
	m_moveStrategy->m_context = this;
}

void PositionController::process(float timestep)
{
	if (m_moveStrategy != 0)
		m_moveStrategy->computeVelSetpoints(timestep);
}

void PositionController::onProcessEnabling()
{
	//m_posSetpoint = m_posInput;
}

bool PositionController::getPositionReached()
{
	if (m_moveStrategy != 0)
		return m_moveStrategy->getPositionReached();
	return false;
}

void PositionController::setVelTunings(float linVelKp, float angVelKp) {
	m_linVelKp = linVelKp;
	m_angVelKp = angVelKp;
}

void PositionController::setVelLimits(float linVelMax, float angVelMax){
	m_linVelMax = linVelMax;
	m_angVelMax = angVelMax;
}

void PositionController::setPosThresholds(float linPosThreshold, float angPosThreshold) {
	m_linPosThreshold = linPosThreshold;
	m_angPosThreshold = angPosThreshold;
}
