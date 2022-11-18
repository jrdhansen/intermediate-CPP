/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
File name: PatternGosperGliderGun.cpp

THIS FILE CONTAINS:
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
= CLASS IMPLEMENTATION PatternGosperGliderGun, DERIVED FROM BASE CLASS DECLARATION Pattern
    = MEMBER METHODS
        = PatternGosperGliderGun (constructor)
        = getSizeX
        = getSizeY
        = getCell
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// PRE-PROCESSOR DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "PatternGosperGliderGun.hpp"

#include "Pattern.hpp"

#include <array>
#include <cstdint>

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// PatternGosperGliderGun METHOD IMPLEMENTATIONS
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Constructor
PatternGosperGliderGun::PatternGosperGliderGun()
{
    // Intialize all values in the array to "false" to begin with.
    for (std::uint8_t row = 0; row < getSizeY(); ++row)
    {
        for (std::uint8_t col = 0; col < getSizeX(); ++col)
        {
            m_grid[row][col] = false;
        }
    }

    // Set certain cells as alive to give the correct initial state (per Wikipedia).
    // Reference --https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life

    // Block on left-hand side.
    m_grid[5][1] = true;
    m_grid[5][2] = true;
    m_grid[6][1] = true;
    m_grid[6][2] = true;
    // Left-part of gun (beak-looking thing)
    m_grid[7][11] = true;
    m_grid[6][11] = true;
    m_grid[5][11] = true;
    m_grid[4][12] = true;
    m_grid[3][13] = true;
    m_grid[3][14] = true;
    m_grid[4][16] = true;
    m_grid[5][17] = true;
    m_grid[6][15] = true;
    m_grid[6][17] = true;
    m_grid[6][18] = true;
    m_grid[7][17] = true;
    m_grid[8][16] = true;
    m_grid[9][14] = true;
    m_grid[9][13] = true;
    m_grid[8][12] = true;
    // Right part of gun (arch-looking thing)
    m_grid[1][25] = true;
    m_grid[2][25] = true;
    m_grid[2][23] = true;
    m_grid[3][21] = true;
    m_grid[3][22] = true;
    m_grid[4][21] = true;
    m_grid[4][22] = true;
    m_grid[5][21] = true;
    m_grid[5][22] = true;
    m_grid[6][23] = true;
    m_grid[6][25] = true;
    m_grid[7][25] = true;
    // Block on the right-hand side
    m_grid[3][35] = true;
    m_grid[3][36] = true;
    m_grid[4][35] = true;
    m_grid[4][36] = true;
}

// Return how many cells the PatternBlinker occupies in X dimension (the number of COLUMNS due to orientation of world in console)
std::uint8_t PatternGosperGliderGun::getSizeX() const
{
    return (static_cast<std::uint8_t>(m_grid[0].size()));
}

// Return how many cells the PatternBlinker occupies in Y dimension (the number of ROWS due to orientation of world in console)
std::uint8_t PatternGosperGliderGun::getSizeY() const
{
    return (static_cast<std::uint8_t>(m_grid.size()));
}

// Return the value of a given cell in PatternBlinker (will either be true or false)
bool PatternGosperGliderGun::getCell(std::uint8_t x, std::uint8_t y) const
{
    // I am using the convention that y=row, x=column (to match Cartesian coordinates, matrix indices convention)
    return (m_grid[x][y]);
}
