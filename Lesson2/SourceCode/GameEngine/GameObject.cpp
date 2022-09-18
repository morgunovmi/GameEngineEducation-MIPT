#include "GameObject.h"

void GameObject::SetPosition(float x, float y, float z)
{
	m_vPosition[0] = x;
	m_vPosition[1] = y;
	m_vPosition[2] = z;

	m_pRenderProxy->SetPosition(m_vPosition);
}

void GameObject::Translate(float delta[])
{
	m_vPosition[0] += delta[0];
	m_vPosition[1] += delta[1];
	m_vPosition[2] += delta[2];

	m_pRenderProxy->SetPosition(m_vPosition);
}

float* GameObject::GetPosition() const
{
	return (float *)m_vPosition;
}