#pragma once
#include "Common.h"

class SCRIPTSYSTEM_API IScriptProxy
{
public:
	virtual void Update(float dt) = 0;
};