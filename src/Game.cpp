//
// Created by Remus on 19/07/2025.
//

#include "Game.h"
#include "imgui.h"
#include "raylib.h"
#include "rlImGui.h"

Game::Game()
{
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

    SetTargetFPS(120);
    systemManager->Init();
}

void Game::DrawUI()
{
    ImGui::SetNextWindowPos(ImVec2(0, static_cast<float>(windowSettings.windowHeight) - 80), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(static_cast<float>(windowSettings.windowWidth), 80), ImGuiCond_Always);

    ImGui::Begin("BottomWindow", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

    if (ImGui::Button("Regenerate"))
    {

    }

    ImGui::NewLine();
    ImGui::End();
}
void Game::Update()
{
    while (!WindowShouldClose())
    {

        systemManager->Update(GetFrameTime());

        BeginDrawing();
        rlImGuiBegin();

        DrawUI();
        ClearBackground(RAYWHITE);

        DrawFPS(0,0);

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