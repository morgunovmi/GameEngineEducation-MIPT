#pragma once

#include "Common.h"
#include "ISoundBackend.h"

#include "fmod.hpp"
#include <memory>
#include <unordered_map>

class SOUNDBACKEND_API FmodBackend : public ISoundBackend {
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void StartSound(const std::string& filePath, bool stream) override;

	~FmodBackend();

private:
	FMOD::System* m_system = nullptr;
	FMOD::Channel* m_channel = nullptr;
	std::unordered_map<std::string, FMOD::Sound*> m_loadedSounds{};
};
