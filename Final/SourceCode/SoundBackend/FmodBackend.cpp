#include "FmodBackend.h"
#include "fmod_errors.h"

#include "Util/LidlAssert.h"

#define CHECK_RESULT(expr)                                          \
do                                                                  \
{                                                                   \
    const auto result = expr;                                       \
    lidl_assert(result == FMOD_OK, "{}", FMOD_ErrorString(result)); \
}                                                                   \
while (false);

void FmodBackend::Init()
{
    CHECK_RESULT(FMOD::System_Create(&m_system));
    CHECK_RESULT(m_system->init(32, FMOD_INIT_NORMAL, nullptr));
}

void FmodBackend::Update()
{
    CHECK_RESULT(m_system->update());
}

void FmodBackend::StartSound(const std::string& fileName, bool stream)
{
    const auto relativePath = "../../../Assets/sounds/" + fileName;
    if (!m_loadedSounds.contains(relativePath))
    {
        FMOD::Sound* sound{};
        if (stream)
        {
            CHECK_RESULT(m_system->createStream(relativePath.c_str(), FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound));
        }
        else
        {
            CHECK_RESULT(m_system->createSound(relativePath.c_str(), FMOD_DEFAULT, 0, &sound));
        }

        CHECK_RESULT(m_system->playSound(sound, 0, false, &m_channel));
        m_loadedSounds[relativePath] = sound;
    } 
    else
    {
        CHECK_RESULT(m_system->playSound(m_loadedSounds[relativePath], 0, false, &m_channel));
    }
}

FmodBackend::~FmodBackend()
{
    for (auto& [path, sound] : m_loadedSounds)
    {
        CHECK_RESULT(sound->release());
    }

    CHECK_RESULT(m_system->close());
    CHECK_RESULT(m_system->release());
}
