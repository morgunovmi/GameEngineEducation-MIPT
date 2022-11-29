#include "FmodBackend.h"
#include "fmod_errors.h"

#include "Util/LidlAssert.h"
#include "Util/Log.h"
#include "Mood.h"
#include <json.hpp>
#include <filesystem>
#include <fstream>

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

void FmodBackend::StartSound(const std::string& fileName, float volume, bool stream, bool loop)
{
    const auto relativePath = "../../../Assets/sounds/" + fileName;

    FMOD::Channel* channel{};
    if (!m_loadedSounds.contains(relativePath))
    {
        FMOD::Sound* sound{};
        if (stream)
        {
            CHECK_RESULT(m_system->createStream(relativePath.c_str(), 
                                loop ? FMOD_LOOP_NORMAL : FMOD_DEFAULT, 0, &sound));
        }
        else
        {
            CHECK_RESULT(m_system->createSound(relativePath.c_str(),
                                loop ? FMOD_LOOP_NORMAL : FMOD_DEFAULT, 0, &sound));
        }

        CHECK_RESULT(m_system->playSound(sound, 0, false, &channel));
        m_loadedSounds[relativePath] = sound;
    } 
    else
    {
        CHECK_RESULT(m_system->playSound(m_loadedSounds[relativePath], 0, false, &channel));
    }

    channel->setVolume(volume / 100.f);
}

void FmodBackend::StartMood(const std::string& moodName)
{
    const auto path = "../../../Assets/moods/" + moodName;
    lidl_assert(std::filesystem::exists(std::filesystem::path{ path }),
                "File {} doesn't exist", moodName);

    if (auto ifs = std::ifstream{ path })
    {
        Mood mood{};
        mood = nlohmann::json::parse(ifs).get<Mood>();

        for (const auto& sound : mood)
        {
            Log("{} : {}", sound.soundName, sound.loop);
            StartSound(sound.soundName, sound.volume, sound.stream, sound.loop);
        }
    }
    else
    {
        lidl_assert(false, "Couldn't parse stream");
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
