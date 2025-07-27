//
// Created by Remus on 27/07/2025.
//


#pragma once
#include <cstdint>
#include <set>
#include <vector>
#include "algorithms/IProceduralInterface.h"
#include "raylib.h"


class World
{

public:
    World(int32_t worldWidth, int32_t worldHeight);

    int32_t GetWidth() const { return width; }
    int32_t GetHeight() const { return height; }
    void Draw();
    void Tick();

private:
    void DrawUI();


    void OnGenerationFinished();
    void OnGenerationStepComplete(const std::vector<GeneratedCell>& updatedCells);


private:
    int32_t reservedUIHeight;
    int32_t width;
    int32_t height;

    Texture2D worldTexture;
    Shader shader;

    std::vector<Color> pixels;
    std::vector<Cell> grid;
    std::set<int32_t> cursor;

    int32_t proceduralSteps;
    int32_t stepsPerGeneration;
    int32_t selectedAlgorithm;
    std::unordered_map<int32_t, std::unique_ptr<IProceduralInterface>> proceduralGenerationMap;
    std::vector<std::string> proceduralGenerationNames;
};
