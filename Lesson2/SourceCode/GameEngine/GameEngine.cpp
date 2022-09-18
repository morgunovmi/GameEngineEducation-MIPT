// GameEngine.cpp : Defines the entry point for the application.
//

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include "GameEngine.h"
#include "RenderEngine.h"
#include "RenderThread.h"
#include "CubeGameObject.h"
#include "GameTimer.h"
#include "WinUtils.h"
#include "Config.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // Enable run-time memory check for debug builds.
#if defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    auto inputConfig = GetInputConfig("config.ini");

    const float moveSpeed = 10.f;

    GameTimer timer;

    auto* const renderEngine = new RenderEngine(hInstance);
    auto* const renderThread = renderEngine->GetRT();

    auto* cube = new CubeGameObject();
    renderThread->EnqueueCommand(RC_CreateCubeRenderObject, cube->GetRenderProxy());

    MSG msg = { 0 };

    timer.Start();
    timer.Reset();

    // Main message loop:
    while (msg.message != (WM_QUIT | WM_CLOSE))
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            PrintKeyboardMessages(msg);

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            timer.Tick();

            float moveDelta[3] = {0, 0, 0};
            if (IsKeyPressed(inputConfig[MoveForward]))
            {
                moveDelta[2] += moveSpeed * timer.DeltaTime();
            }
            if (IsKeyPressed(inputConfig[MoveLeft]))
            {
                moveDelta[0] -= moveSpeed * timer.DeltaTime();
            }
            if (IsKeyPressed(inputConfig[MoveBack]))
            {
                moveDelta[2] -= moveSpeed * timer.DeltaTime();
            }
            if (IsKeyPressed(inputConfig[MoveRight]))
            {
                moveDelta[0] += moveSpeed * timer.DeltaTime();
            }
            if (IsKeyPressed(inputConfig[MoveUp]))
            {
                moveDelta[1] += moveSpeed * timer.DeltaTime();
            }
            if (IsKeyPressed(inputConfig[MoveDown]))
            {
                moveDelta[1] -= moveSpeed * timer.DeltaTime();
            }
            cube->Translate(moveDelta);

            //const auto* pos = cube->GetPosition();
            //wchar_t str[32];
            //swprintf_s(str, L"%f %f %f\n", pos[0], pos[1], pos[2]);
            //OutputDebugString(str);

            renderThread->OnEndFrame();
        }
    }

    return (int) msg.wParam;
}