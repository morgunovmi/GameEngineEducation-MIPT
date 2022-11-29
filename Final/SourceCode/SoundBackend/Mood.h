#pragma once

#include <string>
#include <vector>

#include <json.hpp>

struct Sound {
	std::string soundName;
	float volume; // 0 - 100 range
    bool stream;
    bool loop;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Sound, soundName, volume, stream, loop)

using Mood = std::vector<Sound>;

inline void to_json(nlohmann::json& j, const Mood& mood)
{
    j = nlohmann::json::array();
    for (const auto& sound : mood)
    {
        j.emplace_back(sound);
    }
}

inline void from_json(const nlohmann::json& j, Mood& mood)
{
    for (auto& sound : j.items())
    {
        mood.emplace_back(sound.value().get<Sound>());
    }
}
