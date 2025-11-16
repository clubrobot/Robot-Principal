#include <Arduino.h>

#include "Odometry.h"

#include <math.h>


void Odometry::process(float timestep)
{
	const float dL = m_leftCodewheel ->restart();
	const float dR = m_rightCodewheel->restart();

	const float deltaLinPos = (dL + dR) / 2;
	const float deltaOrthLinPos = fabs(deltaLinPos) * m_slippage;
	const float deltaAngPos = (dR - dL) / m_axleTrack;

	const float avgTheta = m_pos.theta + deltaAngPos / 2;
	m_pos.x     += deltaLinPos * cos(avgTheta) - deltaOrthLinPos * sin(avgTheta);
	m_pos.y     += deltaLinPos * sin(avgTheta) + deltaOrthLinPos * cos(avgTheta);
	m_pos.theta += deltaAngPos;

	m_linVel = deltaLinPos / timestep;
	m_angVel = deltaAngPos / timestep;
}

void Odometry::setAxleTrack   (float axleTrack)   {
	m_axleTrack = axleTrack;
	update();
}

void Odometry::setSlippage   (float slippage)   {
	m_slippage = slippage;
	update();
}

namespace Odometry_RTOS
{

	void process(float timestep);

	void init_odometry()
	{
		params.m_pos = Position();
		params.m_linVel = 0.0;
		params.m_angVel = 0.0;
		params.m_axleTrack = 0.0;
		params.m_slippage = 0.0;
	}

	void setPosition(float x, float y, float theta)
	{
		params.m_pos.x = x;
		params.m_pos.y = y;
		params.m_pos.theta = theta;
	}
	void setAxleTrack(float axleTrack);
	void setSlippage (float slippage);
	void setCodewheels(AbstractCodewheel& leftCodewheel, AbstractCodewheel& rightCodewheel);
	const Position*	getPosition();
	float getLinVel();
	float getAngVel();
	float getAxleTrack();
	float getSlippage ();
}