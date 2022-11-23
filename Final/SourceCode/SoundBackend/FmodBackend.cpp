#include "FmodBackend.h"
#include "fmod_errors.h"

#include <cassert>

#define CHECK_RESULT(result) assert(result == FMOD_OK && FMOD_ErrorString(result))

void FmodBackend::Init()
{
    FMOD_RESULT result;
    FMOD::System* system;
    result = FMOD::System_Create(&system);
    CHECK_RESULT(result);

    m_system = std::unique_ptr<FMOD::System>(system);

    result = m_system->init(32, FMOD_INIT_NORMAL, nullptr);
    CHECK_RESULT(result);
}

void FmodBackend::PlaySound(const std::string& filePath)
{
}
