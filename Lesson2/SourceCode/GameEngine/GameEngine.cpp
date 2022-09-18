// GameEngine.cpp : Defines the entry point for the application.
//

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include <INIReader.h>

#include <filesystem>

#include "GameEngine.h"
#include "RenderEngine.h"
#include "RenderThread.h"
#include "CubeGameObject.h"
#include "GameTimer.h"
#include "Input.h"
#include "ControlConfig.h"

void PrintKeyboardMessages(const MSG& msg)
{
    wchar_t msg_string[32];
    const auto uMsg = msg.message;
    const auto wParam = msg.wParam;
    switch (uMsg)
    {
    case WM_SYSKEYDOWN:
        swprintf_s(msg_string, L"WM_SYSKEYDOWN: 0x%x\n", wParam);
        OutputDebugString(msg_string);
        break;

    case WM_SYSCHAR:
        swprintf_s(msg_string, L"WM_SYSCHAR: %c\n", (wchar_t)wParam);
        OutputDebugString(msg_string);
        break;

    case WM_SYSKEYUP:
        swprintf_s(msg_string, L"WM_SYSKEYUP: 0x%x\n", wParam);
        OutputDebugString(msg_string);
        break;

    case WM_KEYDOWN:
        swprintf_s(msg_string, L"WM_KEYDOWN: 0x%x\n", wParam);
        OutputDebugString(msg_string);
        break;

    case WM_KEYUP:
        swprintf_s(msg_string, L"WM_KEYUP: 0x%x\n", wParam);
        OutputDebugString(msg_string);
        break;

    case WM_CHAR:
        swprintf_s(msg_string, L"WM_CHAR: %c\n", (wchar_t)wParam);
        OutputDebugString(msg_string);
        break;

    }
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // Enable run-time memory check for debug builds.
#if defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    ControlConfig config{};
    INIReader reader("config.ini");

    if (reader.ParseError() < 0) {
        wchar_t str[32];
        swprintf_s(str, L"Couldn't parse config file\n");
        OutputDebugString(str);
        return 1;
    }

    for (const auto& section : reader.GetSections()) {
        for (const auto& field : reader.GetFields(section)) {
            const auto s = reader.Get(section, field, "meme");
            wchar_t str[32];
            swprintf_s(str, L"%s\n", s.c_str());
            OutputDebugString(str);
        }
    }

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
            if (Keyboard::IsKeyPressed(Keyboard::W))
            {
                moveDelta[2] += moveSpeed * timer.DeltaTime();
            }
            if (Keyboard::IsKeyPressed(Keyboard::A))
            {
                moveDelta[0] -= moveSpeed * timer.DeltaTime();
            }
            if (Keyboard::IsKeyPressed(Keyboard::S))
            {
                moveDelta[2] -= moveSpeed * timer.DeltaTime();
            }
            if (Keyboard::IsKeyPressed(Keyboard::D))
            {
                moveDelta[0] += moveSpeed * timer.DeltaTime();
            }
            if (Keyboard::IsKeyPressed(Keyboard::Space))
            {
                moveDelta[1] += moveSpeed * timer.DeltaTime();
            }
            if (Keyboard::IsKeyPressed(Keyboard::LControl))
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