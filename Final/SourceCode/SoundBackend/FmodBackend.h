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
	virtual void StartSound(const std::string& fileName, float volume, bool stream) override;
	virtual void StartMood(const std::string& moodName) override;

	~FmodBackend();

private:
	FMOD::System* m_system = nullptr;
	std::unordered_map<std::string, FMOD::Sound*> m_loadedSounds{};
};
