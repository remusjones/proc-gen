//
// Created by Remus on 27/07/2025.
//


#pragma once
#include <cstdint>

enum class CellType
{
    None,
    Floor
};

struct Cell
{
    CellType cellType;
};

struct Vector2i
{
    Vector2i() : x(0), y(0){}
    Vector2i(const int32_t x, const int32_t y) : x(x), y(y){}
    Vector2i(const Vector2i& other) : x(other.x), y(other.y){}

    static Vector2i Up()    { return {0, -1}; }
    static Vector2i Down()  { return {0, 1}; }
    static Vector2i Left()  { return {-1, 0}; }
    static Vector2i Right() { return {1, 0}; }


    // Correct: return new object by value (not modifying self)
    Vector2i operator+(const Vector2i& other) const
    {
        return Vector2i(this->x + other.x, this->y + other.y);
    }

    Vector2i operator-(const Vector2i& other) const
    {
        return Vector2i(this->x - other.x, this->y - other.y);
    }

    // Correct: modify self, return *this by reference
    Vector2i& operator+=(const Vector2i& other)
    {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

    // Optional: add compound -= operator
    Vector2i& operator-=(const Vector2i& other)
    {
        this->x -= other.x;
        this->y -= other.y;
        return *this;
    }

    int32_t x;
    int32_t y;
};

class CellUtils
{
public:


    static int32_t GetCellNeighbourIndex(const int32_t cellIndex, const Vector2i& direction, const Vector2i& gridExtents)
    {
        Vector2i cellPosition = GetCellPosition(cellIndex, gridExtents);

        cellPosition.x += direction.x;
        cellPosition.y += direction.y;

        return GetCellIndex(cellPosition, gridExtents);
    }

    static bool IsValidPosition(const Vector2i& cellPosition, const Vector2i& gridExtents)
    {
        return !(cellPosition.x < 0 || cellPosition.x > gridExtents.x - 1 || cellPosition.y < 0 || cellPosition.y > gridExtents.y - 1);
    }

    static int32_t GetCellIndex(const Vector2i& cellPosition, const Vector2i& gridExtents)
    {
        return cellPosition.y * gridExtents.x + cellPosition.x;
    }

    static Vector2i GetCellPosition(const int32_t cellIndex, const Vector2i& gridExtents)
    {
        const int32_t x = cellIndex % gridExtents.x;
        const int32_t y = cellIndex / gridExtents.x;

        return Vector2i(x, y);
    }
};
