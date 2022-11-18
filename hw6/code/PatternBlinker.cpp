/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
File name: PatternBlinker.cpp

THIS FILE CONTAINS:
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
= CLASS IMPLEMENTATION PatternBlinker, DERIVED FROM BASE CLASS DECLARATION Pattern
    = MEMBER METHODS
        = PatternBlinker (constructor)
        = getSizeX
        = getSizeY
        = getCell
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// PRE-PROCESSOR DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "PatternBlinker.hpp"

#include "Pattern.hpp"

#include <array>
#include <cstdint>

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// PatternBlock METHOD IMPLEMENTATIONS
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Constructor
PatternBlinker::PatternBlinker()
{
    // Change all m_grid values to true to make correct pattern.
    m_grid[0][0] = true;
    m_grid[1][0] = true;
    m_grid[2][0] = true;
}

// Return how many cells the PatternBlinker occupies in X dimension (the number of COLUMNS due to orientation of world in console)
std::uint8_t PatternBlinker::getSizeX() const
{
    return (static_cast<std::uint8_t>(m_grid[0].size()));
}

// Return how many cells the PatternBlinker occupies in Y dimension (the number of ROWS due to orientation of world in console)
std::uint8_t PatternBlinker::getSizeY() const
{
    return (static_cast<std::uint8_t>(m_grid.size()));
}

// Return the value of a given cell in PatternBlinker (will either be true or false)
bool PatternBlinker::getCell(std::uint8_t x, std::uint8_t y) const
{
    // I am using the convention that y=row, x=column (to match Cartesian coordinates, matrix indices convention)
    return (m_grid[x][y]);
}
