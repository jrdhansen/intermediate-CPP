/*
------------------------------------------------------------------------------------------------------------------------------------------------
Need to include the sortutils.hpp header file to have access to libraries, constants, function prototypes
------------------------------------------------------------------------------------------------------------------------------------------------
*/
#include "sortutils.hpp"

#include <algorithm>
#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <random>
#include <string>
#include <vector>

/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
MAIN FUNCTION IMPLEMENTATION:
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
int main()
{
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // RANDOM NUMBER GENERATION SETUP
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Create a random device (for seeding the random engine)
    std::random_device randDev;
    // Specify the random engine (here, mt19937 is 32-bit Mersenne Twister, call it gen) and use the random device (randDev) to seed it
    std::mt19937 gen(randDev());
    // Specify the distribution: we'll use integers from a uniform distribution (that way we don't have to store as much data in terms of bytes).
    // The prompt specifies that the draws must have values between -10,000,000 and 10,000,000
    std::uniform_int_distribution<int> unifDist(-10'000'000, 10'000'000);

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // CREATING ARRAYS
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Initialize our foundational array to hold the randomly-generated values
    SourceArray origStdArr;
    // Generate a std::array of HOW_MANY_ELEMENTS random integers whose values are determined by our defined distribution (unifDist)
    for (std::uint32_t i = 0; i < HOW_MANY_ELEMENTS; ++i)
    {
        origStdArr[i] = unifDist(gen);
    }

    // PREPARE THE sorted ARRAY, start by copying the values from origStdArr
    SourceArray sorted = origStdArr;
    std::sort(sorted.begin(), sorted.end());

    // PREPARE THE reversed ARRAY, start by copying the values from sorted array
    SourceArray reversed = sorted;
    std::reverse(reversed.begin(), reversed.end());

    // PREPARE THE rotated ARRAY, start by copying the values from sorted array
    SourceArray rotated = sorted;
    std::rotate(rotated.begin(), rotated.begin() + 1, rotated.end());

    // PREPARE THE organ ARRAY, start by copying the values from sorted array
    SourceArray organPipe = sorted;
    organPipeStdArray(organPipe);

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // EVALUATING PERFORMANCE FUNCTION CALLS
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Evaluate performance of the raw, C-style arrays
    evaluateRawArray(origStdArr, sorted, reversed, organPipe, rotated);

    // Evaluate performance of the std::arrays
    evaluateStdArray(origStdArr, sorted, reversed, organPipe, rotated);

    // Evaluate performance of the std::vectors
    evaluateStdVector(origStdArr, sorted, reversed, organPipe, rotated);

    return 0;
}
