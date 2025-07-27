#include "Game.h"
#include "imgui.h"
#include "algorithms/RandomWalk.h"

World::World(int32_t worldWidth, int32_t worldHeight): reservedUIHeight(80), width(worldWidth),
                                                       height(worldHeight - reservedUIHeight), worldTexture(),
                                                       proceduralSteps(1000), stepsPerGeneration(5),
                                                       selectedAlgorithm(0)
{
    pixels = std::vector<Color>(worldWidth * worldHeight);
    grid = std::vector<Cell>(worldWidth * worldHeight);
    std::ranges::fill(pixels, BLACK);
    Image image = {
        .data = pixels.data(),
        .width = worldWidth,
        .height = worldHeight,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    };

    worldTexture = LoadTextureFromImage(image);
    shader = LoadShader(0, "resources/shaders/level_fs.glsl");

    proceduralGenerationNames = {"Random Walk"};
    proceduralGenerationMap[0] = std::make_unique<RandomWalk>();
}

void World::Draw()
{
    DrawUI();

    if (pixels.size() != width * height)
        pixels.resize(width * height);

    for (int i = 0; i < width * height; ++i)
    {
        if (cursor.contains(i)) continue;

        pixels[i] = grid[i].cellType == CellType::None ? BLACK : DARKBLUE;
    }

    for (const int32_t& cursorIndex : cursor)
    {
        pixels[cursorIndex] = RED;
    }

    UpdateTexture(worldTexture, pixels.data());

    float resolution[2] = { static_cast<float>(width), static_cast<float>(height) };
    SetShaderValue(shader, GetShaderLocation(shader, "resolution"), resolution, SHADER_UNIFORM_VEC2);
    SetShaderValueTexture(shader, GetShaderLocation(shader, "cellTex"), worldTexture);

    Rectangle src = { 0, 0, static_cast<float>(GetWidth()), static_cast<float>(GetHeight()) };
    Rectangle dst = {
        0,
        0,
        static_cast<float>(GetScreenWidth()),
        static_cast<float>(GetScreenHeight() - reservedUIHeight)
    };
    DrawTexturePro(worldTexture, src, dst, { 0, 0 }, 0.0f, WHITE);
}

void World::DrawUI()
{
    ImGui::SetNextWindowPos(ImVec2(0, static_cast<float>(GetScreenHeight()) - 80), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(static_cast<float>(GetScreenWidth()), 80), ImGuiCond_Always);

    ImGui::Begin("BottomWindow", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

    if (ImGui::Button("Regenerate"))
    {
        grid = std::vector<Cell>(GetWidth() * GetHeight());
        GenerationSettings settings {
            { GetWidth(), GetHeight() },
            proceduralSteps,
            stepsPerGeneration,
            &grid,
            std::bind(&World::OnGenerationFinished, this),
            std::bind(&World::OnGenerationStepComplete, this, std::placeholders::_1)
        };
        proceduralGenerationMap[selectedAlgorithm]->Initialize(settings);
    }
    ImGui::SameLine();
    ImGui::SetNextItemWidth(150);
    ImGui::Combo("Generation Method", &selectedAlgorithm, proceduralGenerationNames.data()->data(), proceduralGenerationNames.size());
    ImGui::SetNextItemWidth(150);
    ImGui::SliderInt("Generation Amount", &proceduralSteps, 1, 100000);
    ImGui::SetNextItemWidth(150);
    ImGui::SliderInt("Steps per Generation", &stepsPerGeneration, 1, 1000);

    ImGui::End();
}

void World::Tick()
{
    cursor.clear();
    proceduralGenerationMap[selectedAlgorithm]->Step();
}

void World::OnGenerationFinished()
{
}

void World::OnGenerationStepComplete(const std::vector<GeneratedCell>& updatedCells)
{
    for (const auto& [cell, cellIndex]: updatedCells)
    {
        grid[cellIndex] = cell;
        cursor.insert(cellIndex);
    }
}


