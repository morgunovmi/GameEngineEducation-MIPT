#pragma once

#include "CubeGameObject.h"

class JumpingCubeGameObject final : public CubeGameObject {
public:
	JumpingCubeGameObject() : CubeGameObject() {}

	float* GetVelocity() const { return (float*)m_velocity; }
	void SetVelocity(float x, float y, float z)
	{
		m_velocity[0] = x;
		m_velocity[1] = y;
		m_velocity[2] = z;
	}

private:
	float m_velocity[3];
};
