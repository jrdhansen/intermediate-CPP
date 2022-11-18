/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
File name: main.cpp

THIS FILE CONTAINS:
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
= PRE-PROCESSOR DIRECTIVES : need "WordTree.hpp" and "rlutil.h", include all header files from WordTree.(hpp,cpp), don't rely on cascading includes.
= readDictionary FUNCTION IMPLEMENTATION : from Dr. Mathias, reads a "dictionary.txt" file from the "build" folder into a WordTree structure using the "add" method.
= main FUNCTION IMPLEMENTATION
    = read the data into WordTree object
    = execute logic for prediction until user manually quits (closes console, Ctrl+C, etc.)
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// PRE-PROCESSOR DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "WordTree.hpp"
#include "rlutil.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <deque>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// readDictionary FUNCTION IMPLEMENTATION
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
You can use the following code to read the words into your WordTree. 
This code assumes you have written the WordTree class and have the add method available.
Necessary includes: <fstream>, <string>, <memory>, <algorithm>
*/
std::shared_ptr<WordTree> readDictionary(std::string filename)
{
    auto wordTree = std::make_shared<WordTree>();
    std::ifstream inFile = std::ifstream(filename, std::ios::in);

    while (!inFile.eof())
    {
        std::string word;
        std::getline(inFile, word);
        // Need to consume the carriage return character for some systems, if it exists
        if (!word.empty() && word[word.size() - 1] == '\r')
        {
            word.erase(word.end() - 1);
        }
        // Keep only if everything is an alphabetic character -- Have to send isalpha an unsigned char or
        // it will throw exception on negative values; e.g., characters with accent marks.
        if (std::all_of(word.begin(), word.end(), [](unsigned char c) { return std::isalpha(c); }))
        {
            std::transform(word.begin(), word.end(), word.begin(), [](char c) { return static_cast<char>(std::tolower(c)); });
            wordTree->add(word);
        }
    }

    return wordTree;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// main FUNCTION IMPLEMENTATION
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main()
{
    // Create a ptr to a WordTree called treeTest, use Dr. Mathias's readDictionary function to populate the WordTree.
    std::shared_ptr<WordTree> treeTest = readDictionary("dictionary.txt");

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Code below this point controls console interaction with user.
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Set original cursor location (1-based per rlutil.h, so set to origin location).
    const int xOriginal = 1;
    const int yOriginal = 1;
    // Initialize userInput string.
    std::string userInput;
    // Create a counter to keep track of x position in loop.
    int xMoves = xOriginal;

    // Stay in loop until user aborts the task ("Ctrl" + "c" , closes console window, or something similar)
    while (1)
    {
        // Write non-DELETE current userInput to console
        for (unsigned i = 0; i < userInput.size(); ++i)
        {
            // Print the characters in order, move the cursor over 1 each time.
            rlutil::locate(i + 1u, yOriginal);
            rlutil::setChar(userInput.at(i));
        }

        // Move the cursor, get next user input character
        rlutil::locate(xMoves, yOriginal);
        char userChar = static_cast<char>(rlutil::getkey());

        // If the user wants to DELETE or BACKSPACE:
        if ((userChar == rlutil::KEY_BACKSPACE || userChar == rlutil::KEY_DELETE))
        {
            // If userInput is not empty, then remove the last char in userInput string
            if (!userInput.empty())
            {
                // Remove last char from userInput
                userInput.pop_back();
                // Adjust xMoves.
                xMoves -= 1;
                // Move cursor to new location.
                rlutil::locate(xMoves, yOriginal);
                // continue;
            }
            // If userInput is empty, ignore their request and go back to the top of the while loop to get another character
            else
            {
                continue;
            }
        }

        // If the user inputs a character in {'a', 'b', ..., 'z'}
        else
        {
            // If the user isn't deleting, then add the new character to the userInput string.
            std::string userCharStr(1, userChar);
            userInput = userInput.append(userCharStr);
            // Increment xMoves and clear the console.
            ++xMoves;
        }
        // Clear the console
        rlutil::cls();

        // Write non-DELETE current userInput to console
        for (unsigned i = 0; i < userInput.size(); ++i)
        {
            // Print the characters in order, move the cursor over 1 each time.
            rlutil::locate(i + 1u, yOriginal);
            rlutil::setChar(userInput.at(i));
        }
        // Display prediction information
        std::cout << std::endl
                  << std::endl
                  << "--- prediction ---" << std::endl;

        // Generate and display predictions for current userInput
        std::uint8_t numRowsToDisplay = static_cast<std::uint8_t>(rlutil::trows() - 4);
        std::vector<std::string> predWords = treeTest->predict(userInput, numRowsToDisplay);

        for (unsigned i = 0; i < predWords.size(); ++i)
        {
            std::cout << predWords[i] << std::endl;
        }
    }

    return 0;
}
