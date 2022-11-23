#include "SoundSystem.h"
#include "../SoundBackend/FmodBackend.h"

SoundSystem::SoundSystem()
{
	m_soundBackend = std::make_unique<FmodBackend>();
}