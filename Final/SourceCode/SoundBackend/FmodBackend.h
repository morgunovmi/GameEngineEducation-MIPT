#pragma once

#include "Common.h"
#include "ISoundBackend.h"

#include "fmod.hpp"
#include <memory>

class SOUNDBACKEND_API FmodBackend : public ISoundBackend {
public:
	virtual void Init() override;
	virtual void PlaySound(const std::string& filePath) override;
private:
	std::unique_ptr<FMOD::System> m_system;
};
