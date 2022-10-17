#pragma once
#include "Common.h"

#include <memory>

class CScriptProxy;

class SCRIPTSYSTEM_API IScriptSystem
{
public:
	virtual void Update(float dt) = 0;
	virtual std::shared_ptr<CScriptProxy> CreateProxy(const char* filename) = 0;
};
