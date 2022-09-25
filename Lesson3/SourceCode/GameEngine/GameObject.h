#pragma once

#include "Common.h"
#include "RenderProxy.h"

class GameObject
{
public:
	GameObject() = default;

	~GameObject()
	{
		delete m_pRenderProxy;
	}

	void SetPosition(float x, float y, float z);

	float* GetPosition() const { return (float *)m_vPosition; }
	void Translate(float* delta)
	{
		m_vPosition[0] += delta[0];
		m_vPosition[1] += delta[1];
		m_vPosition[2] += delta[2];

		m_pRenderProxy->SetPosition(m_vPosition);
	}

	RenderProxy* const GetRenderProxy() { return m_pRenderProxy; }
protected:
	RenderProxy* m_pRenderProxy;

	float m_vPosition[3];
};

