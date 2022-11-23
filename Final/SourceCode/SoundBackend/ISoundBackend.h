#pragma once

#include "Common.h"

#include <string>

class SOUNDBACKEND_API ISoundBackend {
	virtual void Init() = 0;
	virtual void PlaySound(const std::string& filePath) = 0;
};
