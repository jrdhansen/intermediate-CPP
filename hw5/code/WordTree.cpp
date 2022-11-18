/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
File name: WordTreechpp

THIS FILE CONTAINS:
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
= PRE-PROCESSOR DIRECTIVES (need "WordTree.hpp" and "rlutil.h")
= WordTree CLASS METHOD IMPLEMENTATIONS
    = WordTree : Class constructor.
    = add      : Adds a new word to the tree. If the word already exists there is no duplication.
    = find     : Searches the tree to see if the word is found.
    = predict  : Given the partial (or completed) word, returns a std::vector of up to howMany predicted words.
    = size     : Returns a count of the number of words in the tree. Simply returns the numWordsInTree int initialized with all WordTree instances.
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
// WordTree CLASS METHOD IMPLEMENTATIONS
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
WordTree constructor
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
WordTree::WordTree()
{
    // Call TreeNode construcutor (makes an array of nullptrs) and now ptrToRoot points to this node in memory.
    ptrToRoot = std::make_shared<TreeNode>();
}

/*
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Adds a new word to the tree. If the word already exists there is no duplication.
@param word : a single word from the dictionary being read in (or added manually)
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
void WordTree::add(std::string word)
{
    // Make a ptr to a new node, starting with the root node.
    std::shared_ptr<TreeNode> ptrToNewNode = ptrToRoot;

    // Looping through all characters in a word to create additional children nodes
    for (unsigned i = 0; i < word.size(); ++i)
    {
        // At what position (0,1,...,25) in the alphabet is the current letter?
        auto letterIndex = (word[i] - 'a');
        // Make a new node for this letter (since it's null right now)
        if (ptrToNewNode->children[letterIndex] == nullptr)
        {
            ptrToNewNode->children[letterIndex] = std::make_shared<TreeNode>();
        }
        // Set ptrToNewNode as a ptr to the next child node.
        ptrToNewNode = ptrToNewNode->children[letterIndex];

        // Setting endOfWord bool to true on the last letter in the word
        if ((i == word.length() - 1) && (ptrToNewNode->endOfWord == false))
        {
            ptrToNewNode->endOfWord = true;
            // Increment the numWordsInTree (we'll return this in the "size" method below)
            ++numWordsInTree;
        }
    }
}

/*
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Searches the tree to see if the word is found.
@param word : a single word from the dictionary being read in (or added manually)
@return : true is the word is in the tree, false if not
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
bool WordTree::find(std::string word)
{

    // If an empty string is entered then return false
    if (word.empty())
    {
        return (false);
    }

    // Make a ptr to the next node, starting with the root node.
    std::shared_ptr<TreeNode> ptrToNextNode = ptrToRoot;
    // Looping through all characters in a word to explore children nodes
    for (unsigned i = 0; i < word.size(); ++i)
    {
        // At what position (0,1,...,25) in the alphabet is the current letter?
        auto letterIndex = (word[i] - 'a');
        // Is the ptr for this letter NULL? If so, return false
        if ((*ptrToNextNode).children[letterIndex] == nullptr)
        {
            return (false);
        }
        // Now make the ptrToNextNode point to the appropriate child node
        ptrToNextNode = (*ptrToNextNode).children[letterIndex];
        // If we've reached the end of the word we need to see endOfWord == true,
        // otherwise "word" isn't in the tree.
        if (i == word.length() - 1)
        {
            return (ptrToNextNode->endOfWord);
        }
    }
    // If we have made it this far without returning "true" we know that the word isn't
    // in the tree. Therefore, we will return false.
    return (false);
}

/*
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Given the partial (or completed) word, returns a std::vector of up to howMany predicted words.
Requires a breadth-first search of the tree, after the node where the partial word ends.
@param partial : a partial word (could also be a completed word, e.g. "bad" is partial for "badly")
@param howMany : how many predicted words to return in a vector.
@return        : a std::vector of predicted words based on the "partial" input
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
std::vector<std::string> WordTree::predict(std::string partial, std::uint8_t howMany)
{
    // Initialize empty vector (of strings) in which we store predictions.
    std::vector<std::string> predictions;

    // If the input "partial" is just an empty string, then return the empty predictions vector
    if (partial.empty())
    {
        return (predictions);
    }

    // Find the node where "partial" ends. If it's false, then return an empty predictions vector
    //--------------------------------------------------------------------------------------------
    // Start with the prtToRoot, will update this below to move down the tree.
    std::shared_ptr<TreeNode> ptrToNextNode = ptrToRoot;
    // Loop through until we have the ptr to the node where "partial" ends
    for (unsigned i = 0; i < partial.length(); ++i)
    {
        // Determine the current character of "partial"
        auto letterIndex = (partial[i] - 'a');
        // Move the ptr down a level in the tree to the correct ptr in next node's ptr array
        ptrToNextNode = (ptrToNextNode->children[letterIndex]);
        // Can only access the child if it exists
        if (ptrToNextNode == nullptr)
        {
            // If the entered "partial" has no words (the tree below it doesn't exist)
            // then return the empty "predictions" vector
            //std::string emptyStr = "";
            //predictions.push_back(emptyStr);
            return (predictions);
        }
    }
    // At this point in the program, ptrToNextNode points to the node where "partial" ends

    // Define a struct that holds a ptr to parent TreeNode and the associated string ("partialGrowing") of that node.
    // Shorthand for NodePlusChar will be NPC below.
    struct NodePlusChar
    {
        std::shared_ptr<TreeNode> ptrToParent;
        std::string partialGrowing;
    };
    // The std::deque will keep track of instances of NodePlusChars.
    // std::string predWord will be a string (predicted word) to add to our vector of predictions.
    std::deque<NodePlusChar> predQueue;
    std::string predWord;
    // Initialize predQueue with the last NPC in "partial"
    NodePlusChar npc{ptrToNextNode, partial};
    predQueue.push_back(npc);

    // Doing breadth-first search to find predictions (either until we have howMany, or run out of tree to search).
    //do
    while ((predictions.size() < howMany) && (!predQueue.empty()))
    {
        // Store parent NodePlusChar (NPC) locally, then pop it off the deque
        NodePlusChar parentNPC = predQueue[0];
        predQueue.pop_front();
        // Store ptrs to children nodes as std::array of ptrs
        std::array<std::shared_ptr<TreeNode>, 26> childNodes = (parentNPC.ptrToParent)->children;
        // If the parent node is an endOfWord then add that word to "predictions" (unless partial is already a word)
        if ((parentNPC.ptrToParent->endOfWord) && (partial != parentNPC.partialGrowing))
        {
            std::string newWord = (parentNPC.partialGrowing);
            predictions.push_back(newWord);
        }
        // Add childNodes to the queue as NPC instances
        for (unsigned i = 0; i < childNodes.size(); ++i)
        {
            // Store ptr for the i^th child node
            std::shared_ptr<TreeNode> childPtr = childNodes[i];
            // If the child is a nullptr then we can skip it, otherwise add it to queue
            if (childPtr != nullptr)
            {
                // Determine the letter of the node (e.g. 'a', 'b', ... , 'z')
                char childChar = static_cast<char>(i) + 'a';
                std::string childStr(1, childChar);
                // Add this character (now a 1-char string) to the partialGrowing string.
                childStr = (parentNPC.partialGrowing + childStr);
                // Add the child NodePlusChar to the queue
                NodePlusChar childNPC{childPtr, childStr};
                predQueue.push_back(childNPC);
            }
        }
    }
    return (predictions);
}

/*
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Returns a count of the number of words in the tree. Simply returns the numWordsInTree int initialized with all WordTree instances.
The numWordsInTree int is incremented in the "add" method each time we've added a new word to the tree.
@return : a std::size_t (unsigned integral type) of how many words are in the tree.
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
std::size_t WordTree::size()
{
    return (numWordsInTree);
}
