/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
File name: PatternGlider.cpp

THIS FILE CONTAINS:
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
= CLASS IMPLEMENTATION PatternGlider, DERIVED FROM BASE CLASS DECLARATION Pattern
    = MEMBER METHODS
        = PatternGlider (constructor)
        = getSizeX
        = getSizeY
        = getCell
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// PRE-PROCESSOR DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "PatternGlider.hpp"

#include "Pattern.hpp"

#include <array>
#include <cstdint>

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// PatternGlider METHOD IMPLEMENTATIONS
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Constructor
PatternGlider::PatternGlider()
{
    // Intialize all values in the array to "false" to begin with.
    for (std::uint8_t row = 0; row < getSizeY(); ++row)
    {
        for (std::uint8_t col = 0; col < getSizeX(); ++col)
        {
            m_grid[row][col] = false;
        }
    }

    // Set the correct cells to be alive for initial state of glider (per Wikipedia diagram).
    // Reference --https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
    m_grid[1][1] = true;
    m_grid[2][2] = true;
    m_grid[2][3] = true;
    m_grid[3][1] = true;
    m_grid[3][2] = true;
}

// Return how many cells the PatternBlinker occupies in X dimension (the number of COLUMNS due to orientation of world in console)
std::uint8_t PatternGlider::getSizeX() const
{
    return (static_cast<std::uint8_t>(m_grid[0].size()));
}

// Return how many cells the PatternBlinker occupies in Y dimension (the number of ROWS due to orientation of world in console)
std::uint8_t PatternGlider::getSizeY() const
{
    return (static_cast<std::uint8_t>(m_grid.size()));
}

// Return the value of a given cell in PatternBlinker (will either be true or false)
bool PatternGlider::getCell(std::uint8_t x, std::uint8_t y) const
{
    // I am using the convention that y=row, x=column (to match Cartesian coordinates, matrix indices convention)
    return (m_grid[x][y]);
}
