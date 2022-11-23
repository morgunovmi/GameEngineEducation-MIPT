#include "SoundSystem.h"
#include "../SoundBackend/FmodBackend.h"

SoundSystem::SoundSystem()
{
	m_soundBackend = std::make_unique<FmodBackend>();
	m_soundBackend->Init();
}

void SoundSystem::Update()
{
	m_soundBackend->Update();
}

void SoundSystem::StartSound(const std::string& fileName, bool stream)
{
	m_soundBackend->StartSound(fileName, stream);
}
