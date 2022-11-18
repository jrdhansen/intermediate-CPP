/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
File name: RendererConsole.hpp

THIS FILE CONTAINS:
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
= RendererConsole CLASS, DERIVED FROM Renderer CLASS
    = MEMBER VARIABLES
        = n/a
    = MEMBER METHODS
        = render
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// PRE-PROCESSOR DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma once
#include "LifeSimulator.hpp"
#include "Renderer.hpp"

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// RendererConsole CLASS DECLARATION
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class RendererConsole : public Renderer
{
  public:
    virtual void render(const LifeSimulator& simulation) override;
};
