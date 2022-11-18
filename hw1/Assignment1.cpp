/*
CS 3460, Fall 2019
ASSIGNMENT 1: Nbonacci Number

Author: Jared Hansen
Due: Friday, 09/06/2019
*/




//==============================================================================
// PRE-PROCESSOR DIRECTIVES ====================================================
//==============================================================================
#include <iostream>
#include <string>
#include <cmath>   //cmath is needed in order for the std::abs function to work
				   // on certain g++ compilers








//==============================================================================
// FUNCTION PROTOTYPES =========================================================
//==============================================================================

// This function recursively computes the n^{th} number (second argument) in the
// series sequence (first argument), and returns that n^{th} number.
long nbonacci(unsigned int series, unsigned int n);

// This function determines the value that a series (Fibonacci, etc.) converges
// to -- to a tolerance of 1.0e-06 -- when measuring F(n)/F(n-1) where n is the
// n^{th} element of the sequence.
void computeNbonacciRatio(std::string title, unsigned int series);









//==============================================================================
// MAIN FUNCTION ===============================================================
//==============================================================================
int main() {


	// DISPLAYING THE SEQUENCES ================================================
	//==========================================================================

	// The sample output shows to display the first 20 values in each sequence.
	const int NUM_SEQ_VALS = 20;

	std::cout << std::endl;   // For nicer formatting
	// Fibonacci sequence (series = 2)
	std::cout << "--- Fibonacci Sequence ---" << std::endl;
	for (int i = 0; i < NUM_SEQ_VALS; ++i)
	{
		std::cout << nbonacci(2, i) << "  ";
	}
	std::cout << std::endl;

	// Tribonacci sequence (series = 3)
	std::cout << "--- Tribonacci Sequence ---" << std::endl;
	for (int i = 0; i < NUM_SEQ_VALS; ++i)
	{
		std::cout << nbonacci(3, i) << "  ";
	}
	std::cout << std::endl;

	// Fourbonacci sequence (series = 4)
	std::cout << "--- Fourbonacci Sequence ---" << std::endl;
	for (int i = 0; i < NUM_SEQ_VALS; ++i)
	{
		std::cout << nbonacci(4, i) << "  ";
	}
	std::cout << std::endl;

	// Fivebonacci sequence (series = 5)
	std::cout << "--- Fivebonacci Sequence ---" << std::endl;
	for (int i = 0; i < NUM_SEQ_VALS; ++i)
	{
		std::cout << nbonacci(5, i) << "  ";
	}
	std::cout << std::endl << std::endl;



	// COMPUTING AND DISPLAYING RATIOS =========================================
	//==========================================================================
	computeNbonacciRatio("Fibonacci", 2);
	computeNbonacciRatio("Tribonacci", 3);
	computeNbonacciRatio("Fourbonacci", 4);
	computeNbonacciRatio("Fivebonacci", 5);


	return 0;
}







//==============================================================================
// FUNCTION DEFINITIONS ========================================================
//==============================================================================

long nbonacci(unsigned int series, unsigned int n)
{
	// This if statement creates the opening sequence of 1's for each series
	// (two 1's for Fibonacci, three 1's for Tribonacci, etc.)
	if (n < series)
	{
		return(1);
	}
	// This else statement sums the previous "series" values in the sequence to
	// return the n^{th} value by recursively calling the nbonacci function.
	else
	{
		// This var will hold the n^{th} value in the sequence.
		int nthValue = 0;
		// Sum the previous "series" (e.g. 2, 3, 4, or 5) values in the sequence
		for (unsigned int i = 0; i < series; ++i)
		{
			nthValue += nbonacci(series, (n - (i + 1)));
		}
		return(nthValue);
	}
}


void computeNbonacciRatio(std::string title, unsigned int series)
{
	// Define the tolerance we must get below for abs(newRatio - prevRatio)
	const double TOLERANCE = 0.000001;
	// Iterations to get below tolerance? Start at 0 to get the same count as Dr. Mathias.
	int iterations = 0;
	// Start with by computing the seq val of the 1th element (also the 0th)
	int n = 1;
	// The ratio of F(1)/F(0) = 1 for all sequences, thus initialize to 1
	double prevRatio = 1;
	// Measures absolute difference between newRatio and prevRatio, initialize
	// to 0 to get into the while loop (and it's true for all seq's but Fib)
	double ratioDiff = 0;

	// The == condition gets us past the initial 1's, the >= condition ends
	// the loop once we've achieved a sufficiently-converged estimate.
	while ((ratioDiff == 0) || (ratioDiff >= TOLERANCE))
	{
		// Compute the n^{th} and (n-1)^{th} value in the sequence, their ratio
		unsigned int seqNth = nbonacci(series, n);
		unsigned int seqNthMinus1 = nbonacci(series, (n - 1));
		double newRatio = (static_cast<double>(seqNth) / seqNthMinus1);
		// Determine the difference between this ratio and the previous one
		ratioDiff = std::abs((prevRatio - newRatio));
		// Now the newRatio becomes the prevRatio for the next iteration
		prevRatio = newRatio;

		// Increment the number of iterations and the sequence element index n
		++iterations;
		++n;
	}
	std::cout << title << " ratio approaches " << prevRatio << " after ";
	std::cout << iterations << " iterations" << std::endl;
}