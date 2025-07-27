//
// Created by Remus on 27/07/2025.
//

#include "RandomWalk.h"

#include <random>

RandomWalk::RandomWalk(): configurationSettings(), currentStep(0)
{
}

void RandomWalk::Initialize(GenerationSettings& settings)
{
    configurationSettings = settings;
    currentPosition = {};
    currentStep = 0;
}

void RandomWalk::Step()
{
    if (configurationSettings.grid == nullptr || currentStep >= configurationSettings.proceduralSteps)
        return;

    // update step location
    std::vector<GeneratedCell> stepCells;

    // run for x per step
    for (int32_t i = 0; i < configurationSettings.stepsPerGeneration && currentStep + i < configurationSettings.proceduralSteps; i++)
    {
        // catch any out of bounds directional walking to force it to regenerate
        Vector2i location;
        do
        {
            location = currentPosition + GetRandomDirection();
        }
        while (!CellUtils::IsValidPosition(location, configurationSettings.gridExtents));

        currentPosition = location;
        int32_t cellIndex = CellUtils::GetCellIndex(currentPosition, configurationSettings.gridExtents);

        // copy the cell from the grid, and mutate it
        // todo: evaluate whether we should just modify the grid in-place instead
        const std::vector<Cell>& cells = *configurationSettings.grid;
        Cell cell = cells[cellIndex];
        cell.cellType = CellType::Floor;

        // prepare the callback
        GeneratedCell generatedCell {cell, cellIndex};
        stepCells.push_back(generatedCell);
        currentStep++;
    }

    // notify listeners of the generated change
    configurationSettings.onStepComplete(stepCells);
}
