/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
File name: LifeSimulator.hpp

THIS FILE CONTAINS:
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
= CLASS DECLARATION LifeSimulator
    = MEMBER VARIABLES
        = m_sizeX
        = m_sizeY
        = m_grid
    = MEMBER METHODS
        = LifeSimulator (constructor)
        = insertPattern
        = update
        = getSizeX
        = getSizeY
        = getCell
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// PRE-PROCESSOR DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma once
#include "Pattern.hpp"

#include <cstdint>
#include <vector>

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// LifeSimulator CLASS DECLARATION
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class LifeSimulator
{
  public:
    LifeSimulator(std::uint8_t sizeX, std::uint8_t sizeY);

    void insertPattern(const Pattern& pattern, std::uint8_t startX, std::uint8_t startY);
    void update();

    std::uint8_t getSizeX() const { return m_sizeX; }
    std::uint8_t getSizeY() const { return m_sizeY; }
    // I'm using y=rows and x=columns (due to the console being described that way in rlutil.h)
    // Also, this is consistent with both Cartesian coordinates, and with notation for matrices (e.g. 2-dim arrays).
    bool getCell(std::uint8_t x, std::uint8_t y) const { return m_grid[x][y]; }

  private:
    std::uint8_t m_sizeX;
    std::uint8_t m_sizeY;
    std::vector<std::vector<bool>> m_grid;
};