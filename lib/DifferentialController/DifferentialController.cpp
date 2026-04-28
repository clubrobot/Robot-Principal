#include <Arduino.h>

#include "DifferentialController.h"
#include "Teleplot.h"

#include <future>

void DifferentialController::process(float timestep)
{
	// Compute linear and angular velocities outputs
	m_linVelOutput = m_linPID->compute(m_linSetpoint, m_linInput, timestep);
	m_angVelOutput = m_angPID->compute(m_angSetpoint, m_angInput, timestep);
	//printf("%d, %f, %f, %f, %f\n", millis(), m_linVelOutput, m_linSetpoint, m_linInput, timestep);
	// Convert linear and angular velocities into wheels' velocities
	teleplot.add_variable_float_2decimal("leftWheelSetVelocity", m_linVelOutput - m_angVelOutput * m_axleTrack / 2);
	teleplot.add_variable_float_2decimal("rightWheelSetVelocity", m_linVelOutput + m_angVelOutput * m_axleTrack / 2);
	m_leftWheel ->setVelocity(m_linVelOutput - m_angVelOutput * m_axleTrack / 2);//-
	m_rightWheel->setVelocity(m_linVelOutput + m_angVelOutput * m_axleTrack / 2);//+
}

void DifferentialController::onProcessEnabling()
{
	m_linPID->reset();
	m_angPID->reset();
}

void DifferentialController::onProcessDisabling()
{
	m_linPID->reset();
	m_angPID->reset();
}

void DifferentialController::setAxleTrack   (float axleTrack)   {
	m_axleTrack = axleTrack;
	update();
}