/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
File name: PatternBlinker.hpp

THIS FILE CONTAINS:
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
= CLASS DECLARATION PatternBlinker, DERIVED FROM BASE CLASS DECLARATION Pattern
    = MEMBER VARIABLES
        = m_grid
    = MEMBER METHODS
        = Block (constructor)
        = getSizeX
        = getSizeY
        = getCell
        = getGrid
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// PRE-PROCESSOR DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma once
#include "Pattern.hpp"

#include <array>
#include <cstdint>

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// PatternBlinker CLASS DECLARATION
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class PatternBlinker : public Pattern
{
  public:
    // METHODS
    PatternBlinker();
    virtual std::uint8_t getSizeX() const override;
    virtual std::uint8_t getSizeY() const override;
    virtual bool getCell(std::uint8_t x, std::uint8_t y) const override;
    // MEMBER VARIABLES
    std::array<std::array<bool, 1>, 3> m_grid;
};