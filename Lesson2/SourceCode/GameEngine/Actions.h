#pragma once

enum Action 
{
	MoveForward,
	MoveBack,
	MoveLeft,
	MoveRight,
	MoveUp,
	MoveDown
};

namespace
{
	const std::string actionStrs[] =
	{
		"MoveForward",
		"MoveBack",
		"MoveLeft",
		"MoveRight",
		"MoveUp",
		"MoveDown"
	};

	const std::size_t NUM_ACTIONS = sizeof(actionStrs) / sizeof(*actionStrs);
}

inline std::string GetActionString(Action action)
{
	return actionStrs[action];
}

inline Action GetActionEnum(const std::string& actionStr)
{
	for (std::size_t i = 0; i < NUM_ACTIONS; ++i)
	{
		if (actionStrs[i] == actionStr)
		{
			return static_cast<Action>(i);
		}
	}
	return static_cast<Action>(-1);
}