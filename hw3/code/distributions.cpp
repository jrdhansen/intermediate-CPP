/*
------------------------------------------------------------------------------------------------------------------------------------------------
Need to include the distributions.hpp header file to have access to libraries, the DistributionPair class, and function prototypes
------------------------------------------------------------------------------------------------------------------------------------------------
*/
#include "distributions.hpp"

/*
------------------------------------------------------------------------------------------------------------------------------------------------


FUNCTION IMPLEMENTATIONS:


------------------------------------------------------------------------------------------------------------------------------------------------
*/

/*
------------------------------------------------------------------------------------------------------------------------------------------------
DEFINITION of generateUniformDistribution:
------------------------------------------------------------------------------------------------------------------------------------------------
This function generates howMany random numbers from a uniform[min,max] distribution.
It then bins these howMany numbers into numberBins.
------------------------------------------------------------------------------------------------------------------------------------------------
*/
std::vector<DistributionPair> generateUniformDistribution(std::uint32_t howMany, std::uint32_t min, std::uint32_t max, std::uint8_t numberBins)
{
    // Create a random device
    std::random_device rd;
    // Create a random engine (we'll use default, which uses linear-congruential engine) and seed it using random device
    std::default_random_engine engine(rd());
    // Specify which distribution we'll be pulling randomly-generated numbers from
    std::uniform_int_distribution<> unifDist(min, max);

    // Initialize an empty vector containing elements of type std::uint32_t (will hold our howMany randomly-generated values)
    std::vector<std::uint32_t> randVals;
    // Populate this vector with values from the specified distribution
    for (std::uint32_t i = 0; i < howMany; ++i)
    {
        randVals.push_back(unifDist(engine));
    }

    // Now that we've generated the values we need to bin them and store this info as a vector of DistributionPair vectors
    //------------------------------------------------------------------------------------------------------------------------------------------
    // Initialize a 2-dim vector where the elements are vectors of type DistributionPair
    std::vector<DistributionPair> binned;
    // Determine the minValue of the first bin
    auto minValBinned = min;
    // Determine the maxValue of the last bin
    auto maxValBinned = max;
    // Determine the binWidth for this distribution = (range of binned values + 1)/(numberBins)
    auto binWidth = (std::abs(static_cast<std::int32_t>(minValBinned - maxValBinned)) + 1) / numberBins;

    // Populate a DistributionPair for each bin (its minVal, MaxVal, and number of draws in the bin)
    for (auto i = 0; i < numberBins; ++i)
    {
        // Determine the minValue of the (i)th bin
        auto minValBinI = minValBinned + (i * binWidth);
        // Determine the maxValue of the (i)th bin
        auto maxValBinI = minValBinI + (binWidth - 1);
        // Determine the minValue of the (i+1)th bin
        auto minValBinIplusOne = minValBinI + binWidth;
        // Initialize the count of the (i)th bin to 0
        auto binCount = 0;
        // Determine how many values are in bin i
        for (unsigned randVal = 0; randVal < randVals.size(); ++randVal)
        {
            // Bins nice, "typical" values (the two if statements below handle values on the edges)
            if ((randVals[randVal] >= minValBinI) && (randVals[randVal] < minValBinIplusOne))
            {
                ++binCount;
            }
            // This if statement bins all values below minValBinned into the lowest bin
            if ((i == 0) && (randVals[randVal] < minValBinned))
            {
                ++binCount;
            }
            // This if statement bins all values above maxValBinned into the highest bin
            if ((i == (numberBins - 1)) && (randVals[randVal] > maxValBinned))
            {
                ++binCount;
            }
        }
        // Now that we've counted how many of the random numbers are in that bin, store as a DistributionPair and
        // pushback (store) in binned (a vector of vectors).
        DistributionPair thisBin = DistributionPair(static_cast<std::uint32_t>(minValBinI), static_cast<std::uint32_t>(maxValBinI));
        thisBin.count = binCount;
        binned.push_back(thisBin);
    }

    return binned;
}

/*
------------------------------------------------------------------------------------------------------------------------------------------------
generateNormalDistribution DEFINITION:
------------------------------------------------------------------------------------------------------------------------------------------------
This function generates howMany random numbers from a Normal(mean, stdev) distribution.
It then bins these howMany numbers into numberBins.
------------------------------------------------------------------------------------------------------------------------------------------------
*/
std::vector<DistributionPair> generateNormalDistribution(std::uint32_t howMany, float mean, float stdev, std::uint8_t numberBins)
{
    // Create a random device
    std::random_device rd;
    // Create a random engine (we'll use default, which uses linear-congruential engine) and seed it using random device
    std::default_random_engine engine(rd());
    // Specify which distribution we'll be pulling randomly-generated numbers from
    std::normal_distribution<> normDist{mean, stdev};

    // Initialize an empty vector containing elements of type double (will hold our howMany randomly-generated values)
    std::vector<double> randVals;
    // Populate this vector with values from the specified distribution
    for (std::uint32_t i = 0; i < howMany; ++i)
    {
        randVals.push_back(normDist(engine));
    }

    // Now that we've generated the values we need to bin them and store this info as a vector of DistributionPair vectors
    //------------------------------------------------------------------------------------------------------------------------------------------
    // Initialize a 2-dim vector where the elements are vectors of type DistributionPair
    std::vector<DistributionPair> binned;
    // Determine the minValue of the first bin
    auto minValBinned = (mean - (4 * stdev));
    // Determine the maxValue of the last bin
    auto maxValBinned = (mean + (4 * stdev));
    // Determine the binWidth for this distribution = (range of binned values)/(numberBins)
    auto binWidth = (std::abs(minValBinned - maxValBinned)) / numberBins;

    // Populate a DistributionPair for each bin (its minVal, MaxVal, and number of draws in the bin)
    for (auto i = 0; i < numberBins; ++i)
    {
        // Determine the minValue of the (i)th bin
        auto minValBinI = minValBinned + (i * binWidth);
        // Determine the maxValue of the (i)th bin
        auto maxValBinI = minValBinI + (binWidth - 1);
        // Determine the minValue of the (i+1)th bin
        auto minValBinIplusOne = minValBinI + binWidth;
        // Initialize count of the (i)th bin to 0
        auto binCount = 0;
        // Determine how many values are in bin i
        for (unsigned randVal = 0; randVal < randVals.size(); ++randVal)
        {
            // Bins nice, "typical" values (the two if statements below handle values on the edges)
            if ((randVals[randVal] >= minValBinI) && (randVals[randVal] < minValBinIplusOne))
            {
                ++binCount;
            }
            // This if statement bins all values below minValBinned into the lowest bin
            if ((i == 0) && (randVals[randVal] < minValBinned))
            {
                ++binCount;
            }
            // This if statement bins all values above maxValBinned into the highest bin
            if ((i == (numberBins - 1)) && (randVals[randVal] > maxValBinned))
            {
                ++binCount;
            }
        }
        // Now that we've counted how many of the random numbers are in that bin, store as a DistributionPair and
        // pushback (store) in binned (a vector of vectors).
        DistributionPair thisBin = DistributionPair(static_cast<std::uint32_t>(minValBinI), static_cast<std::uint32_t>(maxValBinI));
        thisBin.count = binCount;
        binned.push_back(thisBin);
    }

    return binned;
}

/*
------------------------------------------------------------------------------------------------------------------------------------------------
generatePoissonDistribution DEFINITION:
------------------------------------------------------------------------------------------------------------------------------------------------
This function generates howMany random numbers from a Poisson(howOften) distribution.
It then bins these howMany numbers into numberBins.
------------------------------------------------------------------------------------------------------------------------------------------------
*/
std::vector<DistributionPair> generatePoissonDistribution(std::uint32_t howMany, std::uint8_t howOften, std::uint8_t numberBins)
{
    // Create a random device
    std::random_device rd;
    // Create a random engine (we'll use default, which uses linear-congruential engine) and seed it using random device
    std::default_random_engine engine(rd());
    // Specify which distribution we'll be pulling randomly-generated numbers from
    std::poisson_distribution<> poisDist(howOften);

    // Initialize an empty vector containing elements of type std::uint32_t (will hold our howMany randomly-generated values)
    std::vector<std::uint32_t> randVals;
    // Populate this vector with values from the specified distribution
    for (std::uint32_t i = 0; i < howMany; ++i)
    {
        randVals.push_back(poisDist(engine));
    }

    // Now that we've generated the values we need to bin them and store this info as a vector of DistributionPair vectors
    //------------------------------------------------------------------------------------------------------------------------------------------
    // Initialize a 2-dim vector where the elements are vectors of type DistributionPair
    std::vector<DistributionPair> binned;
    // Determine the minValue of the first bin, cast it to type uint32_t
    auto minValBinned = 0;
    // Determine the maxValue of the last bin, cast it to type uint32_t
    auto maxValBinned = numberBins - 1;
    // Determine the binWidth for this distribution = (range of binned values + 1)/(numberBins)
    auto binWidth = (std::abs(static_cast<std::int32_t>(minValBinned - maxValBinned)) + 1) / numberBins;

    // Populate a DistributionPair for each bin (its minVal, MaxVal, and number of draws in the bin)
    for (auto i = 0; i < numberBins; ++i)
    {
        // Determine the minValue of the (i)th bin
        auto minValBinI = minValBinned + (i * binWidth);
        // Determine the maxValue of the (i)th bin
        auto maxValBinI = minValBinI + (binWidth - 1);
        // Determine the minValue of the (i+1)th bin
        auto minValBinIplusOne = minValBinI + binWidth;
        // Initialize count of the (i)th bin to 0
        auto binCount = 0;
        // Determine how many values are in bin i
        for (unsigned randVal = 0; randVal < randVals.size(); ++randVal)
        {
            // Bins nice, "typical" values (the two if statements below handle values on the edges)
            if ((randVals[randVal] >= static_cast<unsigned>(minValBinI)) &&
                (randVals[randVal] < static_cast<unsigned>(minValBinIplusOne)))
            {
                ++binCount;
            }
            // This if statement bins all values below minValBinned into the lowest bin
            if ((i == 0) && (randVals[randVal] < static_cast<std::uint32_t>(minValBinned)))
            {
                ++binCount;
            }
            // This if statement bins all values above maxValBinned into the highest bin
            if ((i == (numberBins - 1)) && (randVals[randVal] > static_cast<std::uint32_t>(maxValBinned)))
            {
                ++binCount;
            }
        }
        // Now that we've counted how many of the random numbers are in that bin, store as a DistributionPair and
        // pushback (store) in binned (a vector of vectors)
        DistributionPair thisBin = DistributionPair(static_cast<std::uint32_t>(minValBinI), static_cast<std::uint32_t>(maxValBinI));
        thisBin.count = binCount;
        binned.push_back(thisBin);
    }

    return binned;
}

/*
------------------------------------------------------------------------------------------------------------------------------------------------
plotDistribution DEFINITION:
------------------------------------------------------------------------------------------------------------------------------------------------
This function takes a title, a vector of DistributionPairs (vectors themselves), and an argument for
the number of characters to be used for the bin with the most values. It then outputs the title and a
plot of the data to the console.
------------------------------------------------------------------------------------------------------------------------------------------------
*/
void plotDistribution(std::string title, const std::vector<DistributionPair>& distribution, const std::uint8_t maxPlotLineSize)
{
    //------------------------------------------------------------------------------------------------------------------------------------------
    // Give the name of the distribution
    //------------------------------------------------------------------------------------------------------------------------------------------
    std::cout << title << std::endl;

    //------------------------------------------------------------------------------------------------------------------------------------------
    // Scale the values of the bin counts according to maxPlotLineSize
    //------------------------------------------------------------------------------------------------------------------------------------------
    // Store the value of the first binCount as our initial highBin
    auto highBinVal = distribution[0].count;
    // Check all other values of count to find the bin with the highest count value
    for (uint32_t i = 1; i < distribution.size(); ++i)
    {
        // Store the value of the current bin
        auto currentBinVal = distribution[i].count;
        // If the current bin has a higher count than the previous highest bin val, save a new highBinVal
        if (currentBinVal > highBinVal)
        {
            highBinVal = currentBinVal;
        }
    }
    // Determine the scaling factor: scaleFactor = maxPlotLineSize / biggestBin
    float scaleFactor = (static_cast<float>(maxPlotLineSize) / highBinVal);
    // Make a copy of distribution vector (copyDist), multiply all count values by scaleFactor,
    // round to nearest integer, store as the count values in copyDist
    std::vector<DistributionPair> copyDist = distribution;
    for (unsigned i = 0; i < distribution.size(); ++i)
    {
        copyDist[i].count = static_cast<std::uint32_t>(std::round(scaleFactor * distribution[i].count));
    }

    //------------------------------------------------------------------------------------------------------------------------------------------
    // Graphical output of the scaled distribution
    //------------------------------------------------------------------------------------------------------------------------------------------
    // We know that the bin values for the final bin will be the widest, use these to set maximums
    int lowerBoundWidth = static_cast<std::int8_t>(std::to_string(copyDist[(copyDist.size() - 1u)].minValue).length()) + 1;
    int upperBoundWidth = static_cast<std::int8_t>(std::to_string(copyDist[(copyDist.size() - 1u)].maxValue).length()) + 1;
    // Display each DistributionPair as: [ minBinVal, maxBinVal] : countAsterisks
    for (std::vector<DistributionPair>::iterator iter = copyDist.begin();
         iter != copyDist.end();
         ++iter)
    {
        // Print the bin bounds as [ minVal, maxVal] :
        std::cout << "[" << std::setw(lowerBoundWidth) << iter->minValue;
        std::cout << "," << std::setw(upperBoundWidth) << iter->maxValue << "] : ";
        // Use a for loop to print the number of asterisks in count
        for (unsigned i = 0; i < iter->count; ++i)
        {
            std::cout << "*";
        }
        // Output a newline before moving to the next bin in copyDist
        std::cout << std::endl;
    }
    // Output a couple of blank lines to separate the output for the 3 distributions
    std::cout << std::endl
              << std::endl;
}