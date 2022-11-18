/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
File name: PatternBlock.cpp

THIS FILE CONTAINS:
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
= CLASS IMPLEMENTATION PatternBlock, DERIVED FROM BASE CLASS DECLARATION Pattern
    = MEMBER METHODS
        = Block (constructor)
        = getSizeX
        = getSizeY
        = getCell
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// PRE-PROCESSOR DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "PatternBlock.hpp"

#include "Pattern.hpp"

#include <array>
#include <cstdint>

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// PatternBlock METHOD IMPLEMENTATIONS
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Constructor
PatternBlock::PatternBlock()
{
    // Change all m_grid values to true to make correct pattern.
    m_grid[0][0] = true;
    m_grid[0][1] = true;
    m_grid[1][0] = true;
    m_grid[1][1] = true;
}

// Return how many cells the PatternBlock occupies in X dimension (the number of COLUMNS due to orientation of world in console)
std::uint8_t PatternBlock::getSizeX() const
{
    return (static_cast<std::uint8_t>(m_grid[0].size()));
}

// Return how many cells the PatternBlock occupies in Y dimension (the number of ROWS due to orientation of world in console)
std::uint8_t PatternBlock::getSizeY() const
{
    return (static_cast<std::uint8_t>(m_grid.size()));
}

// Return the value of a given cell in PatternBlock (will either be true or false)
bool PatternBlock::getCell(std::uint8_t x, std::uint8_t y) const
{
    // I am using the convention that y=row, x=column (to match Cartesian coordinates, matrix indices convention)
    return (m_grid[y][x]);
}

/*
//PROBABLY DON'T NEED THIS, PER TALKING TO DEAN
// Return the grid for the PatternBlock class
std::array<std::array<bool, 4>, 4> PatternBlock::getGrid()
{
    return(m_grid);
}
*/

/*
// MAYBE USE THIS FOR THE insertPattern() METHOD IN THE LifeSimulator CLASS
// Return the grid for the PatternBlock class
std::array<std::array<bool, 4>, 4> PatternBlock::getGrid()
{
    for (std::uint8_t i = 0; i < getSizeX(); ++i)
    {
        for (std::uint8_t j = 0; j < getSizeY(); ++j)
        {

        }
    }
}
*/