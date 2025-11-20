#include <Arduino.h>

#include "PID.h"
#include "mathutils.h"


float PID::compute(float setpoint, float input, float timestep)
{
	// Compute the error between the current state and the setpoint
	float currentError = setpoint - input;

	// Compute the error integral
	m_errorIntegral += currentError * timestep;
	m_errorIntegral = saturate(m_errorIntegral, m_minOutput / m_Ki, m_maxOutput / m_Ki);

	// Compute the error derivative
	float errorDerivative = (currentError - m_previousError) / timestep;
	m_previousError = currentError;

	// Compute the PID controller's output
	float output = m_Kp * currentError + m_Ki * m_errorIntegral - m_Kd * errorDerivative;
	return saturate(output, m_minOutput, m_maxOutput);
}

void PID::reset()
{
	m_errorIntegral = 0;
	m_previousError = 0;
}

void PID::setTunings(float Kp, float Ki, float Kd){
	m_Kp = Kp;
	m_Ki = Ki;
	m_Kd = Kd;
}

void PID::setOutputLimits(float minOutput, float maxOutput)
{
	m_minOutput = minOutput;
	m_maxOutput = maxOutput;
}