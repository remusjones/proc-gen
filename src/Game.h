//
// Created by Remus on 19/07/2025.
//
#pragma once
#include <memory>
#include <string>
#include <vector>
#include "raylib.h"
#include "systems/SystemManager.h"

class FallingSandsSystem;

struct WindowSettings
{
    int windowWidth;
    int windowHeight;
    std::string windowTitle;
};

class Game 
{
public:
    Game();

private:
    void Setup();

    void DrawUI();

    void Update();
    void Shutdown();

private:
    WindowSettings windowSettings;
    std::unique_ptr<SystemManager> systemManager;
    int32_t reservedUIHeight = 80;
};
