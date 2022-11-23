#pragma once

#include "Common.h"
#include "ISoundBackend.h"

#include "fmod.hpp"
#include <memory>

class SOUNDBACKEND_API FmodBackend : public ISoundBackend {
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void PlaySound(const std::string& filePath) override;
	~FmodBackend();

private:
	FMOD::System* m_system;
};
