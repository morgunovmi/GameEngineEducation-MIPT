#pragma once

#include <sol/sol.hpp>
#include <string_view>

#include "IScriptProxy.h"

class SCRIPTSYSTEM_API CScriptProxy final : public IScriptProxy
{
public:
	CScriptProxy(std::string_view file);

	virtual void Update(float dt) override;

	sol::state& GetLua() { return lua_script; }
	template<typename T>
	void Set(std::string_view var, T&& value) {
		lua_script[var] = std::forward(value);
	}
private:
	sol::state lua_script;
	sol::protected_function m_update;
};

