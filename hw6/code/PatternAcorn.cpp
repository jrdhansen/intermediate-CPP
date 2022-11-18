/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
File name: PatternAcorn.cpp

THIS FILE CONTAINS:
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
= CLASS IMPLEMENTATION PatternAcorn, DERIVED FROM BASE CLASS DECLARATION Pattern
    = MEMBER METHODS
        = PatternAcorn (constructor)
        = getSizeX
        = getSizeY
        = getCell
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// PRE-PROCESSOR DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "PatternAcorn.hpp"

#include "Pattern.hpp"

#include <array>
#include <cstdint>

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// PatternAcorn METHOD IMPLEMENTATIONS
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Constructor
PatternAcorn::PatternAcorn()
{
    // Intialize all values in the array to "false" to begin with.
    for (std::uint8_t row = 0; row < getSizeY(); ++row)
    {
        for (std::uint8_t col = 0; col < getSizeX(); ++col)
        {
            m_grid[row][col] = false;
        }
    }
    // Change all m_grid values to true to make correct "acorn" pattern.
    m_grid[1][2] = true;
    m_grid[2][4] = true;
    m_grid[3][1] = true;
    m_grid[3][2] = true;
    m_grid[3][5] = true;
    m_grid[3][6] = true;
    m_grid[3][7] = true;
}

// Return how many cells the PatternBlinker occupies in X dimension (the number of COLUMNS due to orientation of world in console)
std::uint8_t PatternAcorn::getSizeX() const
{
    return (static_cast<std::uint8_t>(m_grid[0].size()));
}

// Return how many cells the PatternBlinker occupies in Y dimension (the number of ROWS due to orientation of world in console)
std::uint8_t PatternAcorn::getSizeY() const
{
    return (static_cast<std::uint8_t>(m_grid.size()));
}

// Return the value of a given cell in PatternBlinker (will either be true or false)
bool PatternAcorn::getCell(std::uint8_t x, std::uint8_t y) const
{
    // I am using the convention that y=row, x=column (to match Cartesian coordinates, matrix indices convention)
    return (m_grid[x][y]);
}
