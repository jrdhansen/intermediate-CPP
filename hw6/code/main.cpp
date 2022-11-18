/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
File name: main.cpp

THIS FILE CONTAINS:
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
= Instantiation of several LifeSimulator (LS) objects ("world states").
= Insertion of patterns into the LS objects to create the initial world states.
= Updates to the world states according to the "4 Rules", and animation of the updates (rendered in console).
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// PRE-PROCESSOR DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "LifeSimulator.hpp"
#include "Pattern.hpp"
#include "PatternAcorn.hpp"
#include "PatternBlinker.hpp"
#include "PatternBlock.hpp"
#include "PatternGlider.hpp"
#include "PatternGosperGliderGun.hpp"
#include "Renderer.hpp"
#include "RendererConsole.hpp"
#include "rlutil.h"

#include <cstdint>
#include <memory>
#include <thread>

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// main FUNCTION IMPLEMENTATION
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
    // Get width (x-dimension) and height (y-dimension) of console
    std::uint8_t width = static_cast<std::uint8_t>(rlutil::tcols() - 1u);
    std::uint8_t height = static_cast<std::uint8_t>(rlutil::trows() - 1u);

    // Create instances of each of the 5 pattern classes to be used for the insertPattern method
    PatternAcorn mainAcorn;
    PatternBlock mainBlock;
    PatternBlinker mainBlinker;
    PatternGlider mainGlider;
    PatternGosperGliderGun mainGliderGun;

    // Create four different simulations (instances of LifeSimulator class) to demonstrate the 5 patterns.
    LifeSimulator gosperSimulation(width, height);
    LifeSimulator acornSimulation(width, height);
    LifeSimulator gliderSimulation(width, height);
    LifeSimulator blockBlinkerSimulation(width, height);

    // Define the initial state of the acornSimulation world
    acornSimulation.insertPattern(mainAcorn, 15u, 10u);

    // Define the initial state of the gliderSimulation world
    gliderSimulation.insertPattern(mainGlider, 2u, 2u);
    gliderSimulation.insertPattern(mainGlider, 8u, 2u);
    gliderSimulation.insertPattern(mainGlider, 14u, 2u);
    gliderSimulation.insertPattern(mainGlider, 20u, 2u);
    gliderSimulation.insertPattern(mainGlider, 26u, 2u);
    gliderSimulation.insertPattern(mainGlider, 2u, 8u);
    gliderSimulation.insertPattern(mainGlider, 8u, 8u);
    gliderSimulation.insertPattern(mainGlider, 14u, 8u);
    gliderSimulation.insertPattern(mainGlider, 20u, 8u);
    gliderSimulation.insertPattern(mainGlider, 26u, 8u);
    gliderSimulation.insertPattern(mainGlider, 2u, 14u);
    gliderSimulation.insertPattern(mainGlider, 8u, 14u);
    gliderSimulation.insertPattern(mainGlider, 14u, 14u);
    gliderSimulation.insertPattern(mainGlider, 20u, 14u);
    gliderSimulation.insertPattern(mainGlider, 26u, 14u);

    // Define the initial state of the gosperSimulation world
    gosperSimulation.insertPattern(mainGliderGun, 0u, 0u);

    // Define the initial state of the blockBlinkerSimulation world
    // Stationary (starting out, combining over time)
    blockBlinkerSimulation.insertPattern(mainBlinker, 2u, 2u);
    blockBlinkerSimulation.insertPattern(mainBlinker, 9u, 2u);
    blockBlinkerSimulation.insertPattern(mainBlinker, 16u, 2u);
    blockBlinkerSimulation.insertPattern(mainBlinker, 23u, 2u);
    blockBlinkerSimulation.insertPattern(mainBlinker, 30u, 2u);
    blockBlinkerSimulation.insertPattern(mainBlinker, 37u, 2u);
    blockBlinkerSimulation.insertPattern(mainBlock, 2u, 8u);
    blockBlinkerSimulation.insertPattern(mainBlock, 9u, 8u);
    blockBlinkerSimulation.insertPattern(mainBlock, 16u, 8u);
    blockBlinkerSimulation.insertPattern(mainBlock, 23u, 8u);
    blockBlinkerSimulation.insertPattern(mainBlock, 30u, 8u);
    blockBlinkerSimulation.insertPattern(mainBlock, 37u, 8u);
    // Combining due to proximity, spreads to stationary patterns (the ones above)
    blockBlinkerSimulation.insertPattern(mainBlinker, 41u, 2u);
    blockBlinkerSimulation.insertPattern(mainBlinker, 45u, 2u);
    blockBlinkerSimulation.insertPattern(mainBlinker, 49u, 2u);
    blockBlinkerSimulation.insertPattern(mainBlinker, 53u, 2u);
    blockBlinkerSimulation.insertPattern(mainBlinker, 57u, 2u);
    blockBlinkerSimulation.insertPattern(mainBlock, 41u, 4u);
    blockBlinkerSimulation.insertPattern(mainBlock, 45u, 4u);
    blockBlinkerSimulation.insertPattern(mainBlinker, 49u, 4u);
    blockBlinkerSimulation.insertPattern(mainBlinker, 53u, 4u);
    blockBlinkerSimulation.insertPattern(mainBlinker, 57u, 4u);

    // Instantiate an object of the RendererConsole class, to be used to output simulation worlds.
    RendererConsole mainConsole;

    // Demonstrate 80 updates of the acornSimulation, pausing briefly between each update rendering.
    for (int i = 0; i < 80; ++i)
    {
        mainConsole.render(acornSimulation);
        acornSimulation.update();
        //std::this_thread::sleep_for(std::chrono::nanoseconds(5));
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    // Demonstrate 40 updates of the gliderSimulation, pausing briefly between each update rendering.
    for (int i = 0; i < 40; ++i)
    {
        mainConsole.render(gliderSimulation);
        gliderSimulation.update();
        //std::this_thread::sleep_for(std::chrono::nanoseconds(5));
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    // Demonstrate 150 updates of the gosperSimulation, pausing briefly between each update rendering.
    for (int i = 0; i < 150; ++i)
    {
        mainConsole.render(gosperSimulation);
        gosperSimulation.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    // Demonstrate 80 updates of the blockBlinkerSimulation, pausing briefly between each update rendering.
    for (int i = 0; i < 80; ++i)
    {
        mainConsole.render(blockBlinkerSimulation);
        blockBlinkerSimulation.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }

    return 0;
}
