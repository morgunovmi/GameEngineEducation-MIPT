#include "ScriptSystem.h"
#include "ScriptProxy.h"

CScriptSystem::CScriptSystem()
{
    return;
}

void CScriptSystem::Update(float dt)
{
    for (auto& s : m_scripts) {
        s->Update(dt);
    }
}

std::shared_ptr<CScriptProxy> CScriptSystem::CreateProxy(const char* filename)
{
    return m_scripts.emplace_back(std::make_shared<CScriptProxy>(filename));
}
