#pragma once

#include "CubeGameObject.h"

class RoamingCubeGameObject final : public CubeGameObject {
public:
	RoamingCubeGameObject() : CubeGameObject(), m_speed(5.f) {}

	float GetSpeed() const { return m_speed; }
	void SetSpeed(float speed) { m_speed = speed; }

private:
	float m_speed;
};