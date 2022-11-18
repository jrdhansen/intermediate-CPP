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
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
FUNCTION IMPLEMENTATIONS for additional functions I wrote:
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

// Generic function to display the results of the timing. Pass in the arrayType (a std::string), and then the timed values for sorting each of
// the 5 arrays {random, sorted, reversed, organ, rotated}. Displays this information in the console output.
void outputResults(const std::string& arrayType, const long long int& randomT, const long long int& sortedT, const long long int& reversedT,
                   const long long int& organT, const long long int& rotatedT)
{
    std::cout << "--- " << arrayType << " Performance --- " << std::endl;
    std::cout << "Random Time     : " << randomT << " ms" << std::endl;
    std::cout << "Sorted Time     : " << sortedT << " ms" << std::endl;
    std::cout << "Reversed Time   : " << reversedT << " ms" << std::endl;
    std::cout << "Organ Pipe Time : " << organT << " ms" << std::endl;
    std::cout << "Rotated Time    : " << rotatedT << " ms" << std::endl
              << std::endl;
}

// Generic function for timing sorting of a given array. The data is the std::array passed in,
// the arrayType {"std", "raw", "vec"} indicates whether we need to convert to vector or raw array before timing.
// ONLY THE SORTING ITSELF IS TIMED.
std::chrono::milliseconds timedSort(const SourceArray& data, std::string arrayType)
{
    // Initialize the timed duration (in milliseconds) to 0 for the "data" array
    std::chrono::milliseconds milli(0);
    // See how long it takes to sort the "data" array HOW_MANY_TIMES
    // (don't include time to generate copy of "data" array each loop)
    for (std::uint8_t i = 0; i < HOW_MANY_TIMES; ++i)
    {
        // Make a copy of the constant-reference std::array "data" passed into the function, call it "dataCopy"
        SourceArray dataCopy = data;

        // If the arrayType is "raw" (a raw, C-style array) then use this block to time:
        //-----------------------------------------------------------------------------------------------------------------
        if (arrayType == "raw")
        {
            // Convert the std::array to a raw array called "arrayToSort" using the initializeRawArrayFromStdArray function
            int arrayToSort[HOW_MANY_ELEMENTS];
            initializeRawArrayFromStdArray(data, arrayToSort);
            // Set the clock starting for timing the sort of each raw array
            auto startTime = std::chrono::steady_clock::now();
            // Sort the arrayToSort raw array
            std::sort(arrayToSort, arrayToSort + HOW_MANY_ELEMENTS);
            // End the timing since we've sorted the std::array now
            auto endTime = std::chrono::steady_clock::now();
            // Increment the value of milli_random with how long it took to do sorting this go around
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
            milli += elapsed;
        }
        // If the arrayType is "std" (a std::array) then use this block to time:
        //-----------------------------------------------------------------------------------------------------------------
        if (arrayType == "std")
        {
            // Set the clock starting for timing the sort of each std::array
            auto startTime = std::chrono::steady_clock::now();
            // Sort the random_copy std::array
            std::sort(dataCopy.begin(), dataCopy.end());
            // End the timing since we've sorted the array now
            auto endTime = std::chrono::steady_clock::now();
            // Increment the value of milli_random with how long it took to do sorting this go around
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
            milli += elapsed;
        }
        // If the arrayType is "vec" (a std::vector) then use this block to time:
        //-----------------------------------------------------------------------------------------------------------------
        if (arrayType == "vec")
        {
            // Convert the std::array to a std::vector called "vecToSort"
            std::vector<int> vecToSort(data.begin(), data.end());
            // Set the clock starting for timing the sort of each std::vector
            auto startTime = std::chrono::steady_clock::now();
            // Sort the vecToSort std::vector
            std::sort(vecToSort.begin(), vecToSort.end());
            // End the timing since we've sorted the std::vector now
            auto endTime = std::chrono::steady_clock::now();
            // Increment the value of milli_random with how long it took to do sorting this go around
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
            milli += elapsed;
        }
    }
    return milli;
}

/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
FUNCTION IMPLEMENTATIONS from prompt:
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
IMPLEMENTATION of initializeRawArrayFromStdArray:
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
This function takes in a constant-referenced std::array (source) and an unpopulated raw, "C-style" array (dest).
It populates the "dest" raw array with the "source" values, creating a copy of "source" that is a raw array instead of a std::array.
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
void initializeRawArrayFromStdArray(const std::array<int, HOW_MANY_ELEMENTS>& source, int dest[])
{
    for (unsigned i = 0; i < source.size(); ++i)
    {
        dest[i] = source[i];
    }
}

/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
IMPLEMENTATION of organPipeStdArray:
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
This function re-organizes the values in the data to have an organ pipe structure.
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
void organPipeStdArray(std::array<int, HOW_MANY_ELEMENTS>& data)
{
    // THIS METHOD OF GENERATING ORGANPIPE USES DATA SORTED IN ASECNDING ORDER, but only the first half
    //---------------------------------------------------------------------------------------------------------------------------------------
    // Just in case the std::array passed in isn't sorted, let's re-sort it and store it as std::array "dataCopy"
    SourceArray dataCopy = data;
    std::sort(dataCopy.begin(), dataCopy.end());
    // Now initialize a new array called "organ" in which to store the organ-pipe-arranged values.
    SourceArray organ;
    // We'll want a variable to use instead of typing a casted HOW_MANY_ELEMENTS every time, so let's only do it once
    const int HOW_MANY = static_cast<int>(HOW_MANY_ELEMENTS);
    // Next let's populate the organ std::array, first ascending (the if statement) and then mirrioring it in descent (the else statement)
    for (int i = 0; i < HOW_MANY; ++i)
    {
        // This populates the ascending half of "organ"
        if (i < (HOW_MANY / 2))
        {
            organ[i] = dataCopy[i];
        }
        // This populates the descending half of "organ"
        else
        {
            int organIndex = (HOW_MANY - static_cast<int>(1) - i);
            organ[i] = dataCopy[organIndex];
        }
    }
    // Change the value of the "data" array that was passed in to be our new "organ" array
    data = organ;
}

/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
IMPLEMENTATION of evaluateRawArray:
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
This function takes in the following constant std::array references : {random, sorted, reversed, organPipe, rotated}.
It then times how long it takes to sort each using the std::sort function.
(The std::arrays are converted to raw, C-style arrays in the timedSort function that I wrote above).
The final result is console output reporting how long it took to sort each of the raw, C-style arrays.
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
void evaluateRawArray(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated)
{
    // Output performance for sorting the various raw C-style arrays
    outputResults("Raw Array", timedSort(random, "raw").count(), timedSort(sorted, "raw").count(), timedSort(reversed, "raw").count(),
                  timedSort(organPipe, "raw").count(), timedSort(rotated, "raw").count());
}

/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
IMPLEMENTATION of evaluateStdArray:
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
This function takes in the following constant std::array references : {random, sorted, reversed, organPipe, rotated}.
It then times how long it takes to sort each std::array using the std::sort function.
The final result is console output reporting how long it took to sort each of the std::arrays.
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
void evaluateStdArray(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated)
{
    // Output performance for sorting the various std::arrays
    outputResults("std::array", timedSort(random, "std").count(), timedSort(sorted, "std").count(), timedSort(reversed, "std").count(),
                  timedSort(organPipe, "std").count(), timedSort(rotated, "std").count());
}

/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
IMPLEMENTATION of evaluateStdVector:
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
This function takes in the following constant std::array references : {random, sorted, reversed, organPipe, rotated}.
It then times how long it takes to sort each using the std::sort function.
(The std::arrays are converted to std::vectors in the timedSort function that I wrote above).
The final result is console output reporting how long it took to sort each of the std::vectors.
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
void evaluateStdVector(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated)
{
    // Output performance for sorting the various std::vectors
    outputResults("std::vector", timedSort(random, "vec").count(), timedSort(sorted, "vec").count(), timedSort(reversed, "vec").count(),
                  timedSort(organPipe, "vec").count(), timedSort(rotated, "vec").count());
}
