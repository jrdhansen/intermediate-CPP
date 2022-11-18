/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
File name: RendererConsole.cpp

THIS FILE CONTAINS:
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
= CLASS IMPLEMENTATION RendererConsole, DERIVED FROM Renderer CLASS
    = MEMBER VARIABLES
        = n/a
    = MEMBER METHODS
        = render
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// PRE-PROCESSOR DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "RendererConsole.hpp"

#include "LifeSimulator.hpp"
#include "Renderer.hpp"
#include "rlutil.h"

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// render METHOD IMPLEMENTATION
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void RendererConsole::render(const LifeSimulator& simulation)
{
    // Clear the console, hide cursor before rendering
    rlutil::cls();
    rlutil::hidecursor();

    // Render each alive cell as a white 'X', render dead cells as blank console at that coordinate.
    for (std::uint8_t row = 0u; row < simulation.getSizeY(); ++row)
    {
        for (std::uint8_t column = 0u; column < simulation.getSizeX(); ++column)
        {
            if (simulation.getCell(row, column))
            {
                // Move the cursor to this location in the console using rlutil::locate(). Coordinates are 1-based,
                // so we need to add 1 to row and column so they're in the correct spot in the console.
                rlutil::locate(column + 1u, row + 1u);
                // Use the rlutil::setChar to draw the cell, draw an 'X' for illustration
                rlutil::setColor(rlutil::WHITE);
                rlutil::setChar('X');
            }
        }
    }

    // Show cursor after rendering (per Dr. Mathias's instructions).
    rlutil::showcursor();
    // Reset color after rendering.
    rlutil::resetColor();
}