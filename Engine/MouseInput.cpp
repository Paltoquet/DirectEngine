#include "stdafx.h"
#include "MouseInput.h"
#include "loger.h"

MouseInput::MouseInput()
{
	m_frameTime = 0.0f;
	m_rotationY = 0.0f;
	m_leftTurnSpeed = 0.0f;
	m_rightTurnSpeed = 0.0f;
}

void MouseInput::Turn(float val) {
	m_rotationY += val;
	if (m_rotationY < 0) {
		
	}
}
void MouseInput::GetRotation(float& y)
{
	y = m_rotationY;
	return;
}

void MouseInput::SetFrameTime(float time)
{
	m_frameTime = time;
	return;
}

MouseInput::~MouseInput()
{
}
