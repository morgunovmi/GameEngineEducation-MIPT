#pragma once

#include <unordered_map>

#include <INIReader.h>

#include "Actions.h"
#include "Keys.h"

using InputConfigMap = std::unordered_map<Action, Keyboard::Key>;

namespace
{
	const InputConfigMap defaultInputConfig =
	{
		{ MoveBack, Keyboard::S },
		{ MoveForward, Keyboard::W },
		{ MoveLeft, Keyboard::A },
		{ MoveRight, Keyboard::D },
		{ MoveUp, Keyboard::Space },
		{ MoveDown, Keyboard::LControl }
	};
}

inline InputConfigMap GetInputConfig(const std::string& configFilePath)
{
	auto inputConfig = defaultInputConfig;
	if (configFilePath.empty())
	{
		return inputConfig;
	}

	INIReader reader(configFilePath);

	if (reader.ParseError() < 0) {
		wchar_t str[32];
		swprintf_s(str, L"Couldn't parse config file\n");
		OutputDebugString(str);
		return {};
	}

	for (const auto& field : reader.GetFields("Keyboard")) {
		const auto& value = reader.Get("Keyboard", field, "Undefined");

		wchar_t str[32];
		swprintf_s(str, L"%s : %s\n", 
			convert_utf8_to_wstring(field).c_str(),
			convert_utf8_to_wstring(value).c_str());
		OutputDebugString(str);

		inputConfig[GetActionEnum(field)] = Keyboard::GetKeyEnum(value);
	}
	return inputConfig;
}