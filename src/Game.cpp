//
// Created by Remus on 19/07/2025.
//

#include "Game.h"
#include "imgui.h"
#include "raylib.h"
#include "rlImGui.h"

Game::Game()
{
    windowSettings.drawFPS = false;
    windowSettings.windowWidth = 800;
    windowSettings.windowHeight = 450;
    windowSettings.windowTitle = "proc-gen";

    Setup();
    Update();
    Shutdown();
}

void Game::Setup()
{
    InitWindow(windowSettings.windowWidth, windowSettings.windowHeight, windowSettings.windowTitle.c_str());

    rlImGuiSetup(true);
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    systemManager = std::make_unique<SystemManager>();
    world = std::make_unique<World>(windowSettings.windowWidth / 3, windowSettings.windowHeight / 3);

    SetTargetFPS(120);
    systemManager->Init();
}


void Game::Update()
{
    while (!WindowShouldClose())
    {
        systemManager->Update(GetFrameTime());
        world->Tick();

        BeginDrawing();
        rlImGuiBegin();

        ClearBackground(RAYWHITE);

        world->Draw();

        if (windowSettings.drawFPS)
        {
            DrawFPS(0,0);
        }

        rlImGuiEnd();
        EndDrawing();
    }
}

void Game::Shutdown()
{
    systemManager->Shutdown();
    rlImGuiShutdown();
    CloseWindow();
}