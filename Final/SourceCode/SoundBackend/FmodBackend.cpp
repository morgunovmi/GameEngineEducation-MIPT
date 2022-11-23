#include "FmodBackend.h"
#include "fmod_errors.h"

#include <cassert>

#define CHECK_RESULT(result) assert(result == FMOD_OK && FMOD_ErrorString(result))

void FmodBackend::Init()
{
    CHECK_RESULT(FMOD::System_Create(&m_system));
    CHECK_RESULT(m_system->init(32, FMOD_INIT_NORMAL, nullptr));
}

void FmodBackend::Update()
{
    CHECK_RESULT(m_system->update());
}

void FmodBackend::PlaySound(const std::string& filePath)
{
}

FmodBackend::~FmodBackend()
{
    CHECK_RESULT(m_system->close());
    CHECK_RESULT(m_system->release());
}
