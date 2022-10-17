#include "ScriptProxy.h"
#include "Log.h"
#include <cassert>

CScriptProxy::CScriptProxy(std::string_view file)
{
	lua_script.open_libraries(sol::lib::base);
	const auto res = lua_script.load_file(file.data());
	if (!res.valid()) {
		sol::error err = res;
		LogError("Couldn't load lua file: %s", err.what());
	}
	m_update = static_cast<sol::protected_function>(res);
}

void CScriptProxy::Update(float dt)
{
	const auto res = m_update(dt);
	if (!res.valid()) {
		sol::error err = res;
		LogError("Couldn't run update: %s", err.what());
	}
	else {
		LogZA("Updating with dt = %f\n", dt);
	}
}