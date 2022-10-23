// GameEngine.cpp : Defines the entry point for the application.
//

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "GameEngine.h"
#include "RenderEngine.h"
#include "RenderThread.h"
#include "GameTimer.h"
#include "InputHandler.h"
#include "EntitySystem/EntitySystem.h"
#include "ScriptSystem.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // Enable run-time memory check for debug builds.
#if defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    GameTimer timer;

    auto renderEngine = std::make_unique<RenderEngine>(hInstance);
    auto* renderThread = renderEngine->GetRT();
    auto inputHandler = std::make_unique<InputHandler>();
    auto scriptSystem = std::make_unique<CScriptSystem>();

    EntitySystem* entitySystem = new EntitySystem(renderEngine.get(),
                                                  inputHandler.get(),
                                                  scriptSystem.get(),
                                                  "../../../Assets/worlds/world.xml");

    MSG msg = { 0 };

    timer.Start();
    timer.Reset();

    // Main message loop:
    while (msg.message != (WM_QUIT | WM_CLOSE))
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            inputHandler->Update();
            scriptSystem->Update(timer.DeltaTime());
            entitySystem->Update();

            timer.Tick();

            renderThread->OnEndFrame();
        }
    }

    return (int) msg.wParam;
}