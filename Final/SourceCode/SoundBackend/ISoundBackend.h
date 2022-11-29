#pragma once

#include "Common.h"

#include <string>

class SOUNDBACKEND_API ISoundBackend {
public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void StartSound(const std::string& fileName, float volume, bool stream, bool loop) = 0;
	virtual void StartMood(const std::string& moodName) = 0;
};
