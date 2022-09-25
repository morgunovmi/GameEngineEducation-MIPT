// GameEngine.cpp : Defines the entry point for the application.
//

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include <memory>
#include <unordered_map>
#include <random>

#include "GameEngine.h"
#include "RenderEngine.h"
#include "RenderThread.h"
#include "CubeGameObject.h"
#include "GameTimer.h"
#include "InputHandler.h"
#include "Objects.h"

using GameObjectMap = std::unordered_map<std::unique_ptr<GameObject>, EObjectType>;

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

    std::random_device rd{};
    std::default_random_engine dre{ rd() };
    std::uniform_int_distribution objDistr{ 0, 2 };

    GameObjectMap objects{};
    for (int i = -5; i < 5; ++i)
    {
        for (int j = -5; j < 5; j++)
        {
            const auto objType = static_cast<EObjectType>(objDistr(dre));
            switch (objType)
            {
            case eOT_Roaming:
            {
                auto cube = std::make_unique<RoamingCubeGameObject>();
                cube->SetPosition(i * 3.0, 0, j * 3.0);
                renderThread->EnqueueCommand(RC_CreateCubeRenderObject, cube->GetRenderProxy());
                objects.insert(std::make_pair(std::move(cube), eOT_Roaming));
                break;
            }
            case eOT_Jumping:
            {
                auto cube = std::make_unique<JumpingCubeGameObject>();
                cube->SetPosition(i * 3.0, 4, j * 3.0);
                renderThread->EnqueueCommand(RC_CreateCubeRenderObject, cube->GetRenderProxy());
                objects.insert(std::make_pair(std::move(cube), eOT_Jumping));
                break;
            }
            case eOT_Controllable:
            {
                auto cube = std::make_unique<ControllableCubeGameObject>();
                cube->SetPosition(i * 3.0, 0, j * 3.0);
                renderThread->EnqueueCommand(RC_CreateCubeRenderObject, cube->GetRenderProxy());
                objects.insert(std::make_pair(std::move(cube), eOT_Controllable));
                break;
            }
            default:
                assert(0 && "Undefined object type");
            }
        }
    }

    MSG msg = { 0 };

    timer.Start();
    timer.Reset();

    float gravity = -.981f;

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
            timer.Tick();
            inputHandler->Update();
            
            for (const auto& [obj, type] : objects)
            {
                switch (type)
                {
                case eOT_Roaming:
                {
                    auto* roaming = static_cast<RoamingCubeGameObject*>(obj.get());
                    auto* curPos = roaming->GetPosition();
                    roaming->SetPosition(curPos[0], curPos[1], curPos[2] + 0.5 * sin(timer.TotalTime() * roaming->GetSpeed()));
                    break;
                }
                case eOT_Jumping:
                {
                    auto* jumping = static_cast<JumpingCubeGameObject*>(obj.get());

                    auto* curVel = jumping->GetVelocity();
                    curVel[1] += gravity * timer.DeltaTime();

                    auto *curPos = jumping->GetPosition();
                    curPos[1] += curVel[1] * timer.DeltaTime();

                    if (curPos[1] < 0.0f)
                    {
                        curVel[1] = std::abs(curVel[1]);
                    }

                    jumping->SetVelocity(curVel[0], curVel[1], curVel[2]);
                    jumping->SetPosition(curPos[0], curPos[1], curPos[2]);
                    break;
                }
                case eOT_Controllable:
                {
                    auto* controllable = static_cast<ControllableCubeGameObject*>(obj.get());
                    float moveDelta[3] = { 0, 0, 0 };
                    const auto acc = controllable->GetAcc() * timer.DeltaTime();
                    if (inputHandler->GetInputState().test(eIC_GoLeft))
                        moveDelta[0] -= acc;
                    if (inputHandler->GetInputState().test(eIC_GoRight))
                        moveDelta[0] += acc;
                    if (inputHandler->GetInputState().test(eIC_GoBack))
                        moveDelta[2] -= acc;
                    if (inputHandler->GetInputState().test(eIC_GoForward))
                        moveDelta[2] += acc;
                    obj->Translate(moveDelta);
                    break;
                }
                default:
                    assert(0 && "Undefined object");
                }
            }

            renderThread->OnEndFrame();
        }
    }

    return (int) msg.wParam;
}
