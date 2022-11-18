/*
------------------------------------------------------------------------------------------------------------------------------------------------
Need to include the distributions.hpp header file to have access to libraries, the DistributionPair class, and function prototypes
------------------------------------------------------------------------------------------------------------------------------------------------
*/
#include "distributions.hpp"

int main()
{
    // UNIFORM DISTRIBUTION --------------------------------------------------------------------------------------------------------------------
    // Generate howMany draws from the specified uniform distribution
    auto uniform = generateUniformDistribution(100000, 0, 79, 40);
    // Plot the generated distribution
    plotDistribution("--- Uniform ---", uniform, 80);

    // NORMAL DISTRIBUTION ---------------------------------------------------------------------------------------------------------------------
    // Generate howMany draws from the specified normal distribution
    auto normal = generateNormalDistribution(100000, 50, 5, 40);
    // Plot the generated distribution
    plotDistribution("--- Normal ---", normal, 80);

    // POISSON DISTRIBUTION --------------------------------------------------------------------------------------------------------------------
    // Generate howMany draws from the specified Poisson distribution
    auto poisson = generatePoissonDistribution(100000, 6, 40);
    // Plot the generated distribution
    plotDistribution("--- Poisson ---", poisson, 80);

    return 0;
}