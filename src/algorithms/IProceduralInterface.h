//
// Created by Remus on 27/07/2025.
//


#pragma once
#include <cstdint>
#include <functional>
#include "Cell.h"

struct GeneratedCell
{
    Cell cell;
    int32_t cellIndex;
};

struct GenerationSettings
{
    Vector2i gridExtents;
    int32_t proceduralSteps;
    int32_t stepsPerGeneration;

    std::vector<Cell>* grid;
    std::function<void()> onFinished;
    std::function<void(const std::vector<GeneratedCell>&)> onStepComplete;
};

class IProceduralInterface
{
public:
    virtual ~IProceduralInterface() = default;
    virtual void Initialize(GenerationSettings& settings) = 0;
    virtual void Step() = 0;
};
