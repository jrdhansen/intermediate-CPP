/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
File name: Renderer.hpp

THIS FILE CONTAINS:
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
= Renderer CLASS
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

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Renderer CLASS & METHOD PROTOTYPE
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class Renderer
{
  public:
    // The "render" method is a pure virtual method (thanks to the = 0 syntax at the end).
    // Override with render method in derived class, RendererConsole class.
    virtual void render(const LifeSimulator& simulation) = 0;
};