#pragma once

#include "Common.h"
#include "../SoundBackend/ISoundBackend.h"

#include <memory>

class SOUNDSYSTEM_API SoundSystem {
public:
	SoundSystem();
	void Update();

private:
	std::unique_ptr<ISoundBackend> m_soundBackend;
};