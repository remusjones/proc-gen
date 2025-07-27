//
// Created by Remus on 19/07/2025.
//
#pragma once
#include <memory>
#include <string>
#include <vector>
#include "raylib.h"
#include "World.h"
#include "systems/SystemManager.h"

class FallingSandsSystem;

struct WindowSettings
{
    bool drawFPS;
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
    void Update();
    void Shutdown();

private:
    WindowSettings windowSettings;
    std::unique_ptr<SystemManager> systemManager;
    std::unique_ptr<World> world;
};
