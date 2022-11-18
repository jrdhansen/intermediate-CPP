/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
File name: LifeSimulator.cpp

THIS FILE CONTAINS:
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
= CLASS IMPLEMENTATION LifeSimulator
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
#include "LifeSimulator.hpp"

#include "Pattern.hpp"

#include <array>
#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// LifeSimulator METHOD IMPLEMENTATIONS
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Constructor, using direct initialization
LifeSimulator::LifeSimulator(std::uint8_t sizeX, std::uint8_t sizeY) :
    m_sizeX(sizeX),
    m_sizeY(sizeY)
{
    // IMPORTANT NOTE: I AM ASSUMING THE FIRST PARAM, sizeX, REPRESENTS THE NUMBER OF COLUMNS,
    //                 AND THAT sizeY REPRESENTS THE NUMBER OF ROWS IN THE CONSOLE ("THE WORLD").

    // Create m_grid based on sizeY and sizeX, initially populate with all false (all dead cells).
    for (std::uint8_t row = 0; row < m_sizeY; ++row)
    {
        std::vector<bool> newRow;
        m_grid.push_back(newRow);
        for (std::uint8_t column = 0; column < m_sizeX; ++column)
        {
            m_grid[row].push_back(false);
        }
    }
}

void LifeSimulator::insertPattern(const Pattern& pattern, std::uint8_t startX, std::uint8_t startY)
{
    // Verify that we can insert the pattern (is within top/left of board AND within bottom/right of board), then insert pattern.
    std::uint8_t patternEndX = (startX + pattern.getSizeX() - 1u);
    std::uint8_t patternEndY = (startY + pattern.getSizeY() - 1u);

    // Pattern can't go off the bottonm-right of board (don't need to check startX and startY since they're unsigned,
    // which necessarily means that they're non-negative so they can't be out-of-bounds of the console.
    if ((patternEndX < m_sizeX) && (patternEndY < m_sizeY))
    {
        for (std::uint8_t row = startY; row < startY + pattern.getSizeY(); ++row)
        {
            for (std::uint8_t col = startX; col < startX + pattern.getSizeX(); ++col)
            {
                // Insert the cell values of the pattern in the appropriate cells in the world's m_grid.
                m_grid[row][col] = pattern.getCell((row - startY), (col - startX));
            }
        }
    }
}

void LifeSimulator::update()
{
    // Create a dynamic (heap-allocated) blank grid. Access with a smart pointer. Call it ptrToUpdateGrid.
    // Use this to keep track of updated cells so we don't alter the current world state.
    auto ptrToUpdateGrid = std::make_unique<std::vector<std::vector<bool>>>();

    // For each currentCell in m_grid, we're going to get the updated cell status and add it to the heap-allocated grid.
    for (std::uint8_t currentY = 0u; currentY < m_sizeY; ++currentY)
    {
        for (std::uint8_t currentX = 0u; currentX < m_sizeX; ++currentX)
        {
            // Set values of minX, minY, maxX, maxY based on currentX and currentY.
            std::uint8_t minX = currentX - 1u;
            std::uint8_t minY = currentY - 1u;
            std::uint8_t maxX = currentX + 1u;
            std::uint8_t maxY = currentY + 1u;
            // Adjust minX if currentX is on LEFT EDGE.
            if (currentX == 0)
            {
                minX = currentX;
            }
            // Adjust minY if currentY is on TOP EDGE.
            if (currentY == 0)
            {
                minY = currentY;
            }
            // Adjust maxX if currentX is on RIGHT EDGE.
            if (currentX == m_sizeX - 1u)
            {
                maxX = currentX;
            }
            // Adjust maxY if currentY is on BOTTOM EDGE.
            if (currentY == m_sizeY - 1u)
            {
                maxY = currentY;
            }

            // Initialize, and then count, aliveNeighbors of currentCell.
            int aliveNeighbors = 0;
            for (auto xNbr = minX; xNbr <= maxX; ++xNbr)
            {
                for (auto yNbr = minY; yNbr <= maxY; ++yNbr)
                {
                    if (!(xNbr == currentX && yNbr == currentY)) // currentCell is not considered a neighbor of currentCell
                    {
                        if (getCell(yNbr, xNbr))
                        {
                            ++aliveNeighbors;
                        }
                    }
                }
            }

            // Now that we have a count of aliveNeighbors for currentCell in m_grid, use the "4 Rules" to udpate its status in heap grid.
            bool currentCell = getCell(currentY, currentX);

            //-------------------------------------------------------------------------
            // FOR CURRENTLY-LIVE CELLS : RULES 1, 2, and 3.
            //-------------------------------------------------------------------------
            // RULE 1 : any live cell with fewer than 2 aliveNeighbors dies
            // RULE 3 : any live cell with more than 3 aliveNeighbors dies
            // RULE 2 : any live cell with 2 or 3 aliveNeighbors lives (implicit in logic below, just leave currentCell as true)
            if (currentCell)
            {
                if (aliveNeighbors < 2 || aliveNeighbors > 3)
                {
                    currentCell = false;
                }
            }
            //-------------------------------------------------------------------------
            // FOR CURRENTLY-DEAD CELLS : RULE 4
            //-------------------------------------------------------------------------
            // RULE 4 : any dead cell with exactly 3 aliveNeighbors becomes a live cell
            else
            {
                if (aliveNeighbors == 3)
                {
                    currentCell = true;
                }
            }

            // Add a new row to our updateGrid.
            std::vector<bool> newRow;
            ptrToUpdateGrid->push_back(newRow);

            // Update currentCell in the heap-allocated (*ptrToUpdateGrid) updated-world grid.
            (*ptrToUpdateGrid)[currentY].push_back(currentCell);
        }
    }

    // Now that we have an updated m_grid sitting on the heap (accessible with the ptrToUpdateGrid pointer), set m_grid to this updated grid
    m_grid = (*ptrToUpdateGrid);
}