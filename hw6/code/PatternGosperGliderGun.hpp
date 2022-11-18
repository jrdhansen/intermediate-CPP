/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
File name: PatternGosperGliderGun.hpp

THIS FILE CONTAINS:
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
= CLASS DECLARATION PatternGosperGliderGun, DERIVED FROM BASE CLASS DECLARATION Pattern
    = MEMBER VARIABLES
        = m_grid
    = MEMBER METHODS
        = PatternGosperGliderGun (constructor)
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
// PatternGosperGliderGun CLASS DECLARATION
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class PatternGosperGliderGun : public Pattern
{
  public:
    // METHODS
    PatternGosperGliderGun();
    virtual std::uint8_t getSizeX() const override;
    virtual std::uint8_t getSizeY() const override;
    virtual bool getCell(std::uint8_t x, std::uint8_t y) const override;
    // MEMBER VARIABLES
    std::array<std::array<bool, 38>, 11> m_grid;
};
