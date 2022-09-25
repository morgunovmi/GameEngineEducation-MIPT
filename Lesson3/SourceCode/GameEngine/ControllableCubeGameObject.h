#pragma once

#include "CubeGameObject.h"

class ControllableCubeGameObject final : public CubeGameObject {
public:
	ControllableCubeGameObject() : CubeGameObject(), m_acceleration(2.f) {}

	float GetAcc() const { return m_acceleration; }
private:
	float m_acceleration;
};

