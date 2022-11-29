#pragma once

#include "Common.h"
#include "../SoundBackend/ISoundBackend.h"

#include <memory>

class SOUNDSYSTEM_API SoundSystem {
public:
	SoundSystem();
	void Update();
	void StartSound(const std::string& fileName, float volume, bool stream, bool loop);
	void StartMood(const std::string& moodName);

private:
	std::unique_ptr<ISoundBackend> m_soundBackend;
};