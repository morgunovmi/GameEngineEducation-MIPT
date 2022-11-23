#pragma once

#include "Common.h"

#include <memory>

class ISoundBackend;

class SOUNDSYSTEM_API SoundSystem {
public:
	SoundSystem();

private:
	std::unique_ptr<ISoundBackend> m_soundBackend;
};