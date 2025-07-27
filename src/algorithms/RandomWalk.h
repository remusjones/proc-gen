//
// Created by Remus on 27/07/2025.
//


#pragma once
#include <random>

#include "Cell.h"
#include "IProceduralInterface.h"

class RandomWalk : public IProceduralInterface
{
public:
    RandomWalk();
    void Initialize(GenerationSettings& settings) override;
    void Step() override;

    Vector2i GetRandomDirection()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(0, 4);

        switch (distr(gen))
        {
            case 0: return  Vector2i::Up();
            case 1: return  Vector2i::Down();
            case 2: return  Vector2i::Left();
            case 3: return  Vector2i::Right();
            default: return Vector2i::Right(); // bias to the right
        }
    }
private:
    GenerationSettings configurationSettings;
    int32_t currentStep;
    Vector2i currentPosition;
};
