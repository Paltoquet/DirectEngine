#pragma once
class MouseInput
{
public:
	MouseInput();
	~MouseInput();

public:
	void SetFrameTime(float);
	void GetRotation(float&);

	void Turn(float);

private:
	float m_frameTime;
	float m_rotationY;
	float m_leftTurnSpeed, m_rightTurnSpeed;
};

