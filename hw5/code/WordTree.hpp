/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
File name: WordTree.hpp

THIS FILE CONTAINS:
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
= PRE-PROCESSOR DIRECTIVES : necessary header files, "pragma once" so that the compiler doesn't do more work than necessary.
= WordTree CLASS
    = MEMBER VARIABLES: 
        = nested "TreeNode" class
            = MEMBER VARIABLES
                = bool endOfWord
                = std::array<std::shared_ptr<TreeNode>, 26> children
        = std::shared_ptr<TreeNode> ptrToRoot
        = int numWordsInTree
    = MEMBER FUNCTIONS: (implementations in WordTree.cpp)
        = WordTree default constructor
        = add
        = find
        = predict
        = size 
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// PRE-PROCESSOR DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma once
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// WordTree CLASS & METHOD PROTOTYPE
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class WordTree
{

  public:
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // WordTree MEMBER VARIABLES
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Create a class for TreeNode nested within WordTree.
    class TreeNode
    {
      public:
        //-------------------------------------------------------------------------------------------------------------------------------------------------------------------
        // TreeNode MEMBER FUNCTIONS
        //-------------------------------------------------------------------------------------------------------------------------------------------------------------------
        // TreeNode constructor intializes a node with an array of 26 shared_ptrs (nullptrs to begin with) and sets endOfWord bool to false.
        TreeNode()
        {
            this->endOfWord = false;
            this->children = std::array<std::shared_ptr<TreeNode>, 26>{nullptr};
        }
        //-------------------------------------------------------------------------------------------------------------------------------------------------------------------
        // TreeNode MEMBER VARIABLES
        //-------------------------------------------------------------------------------------------------------------------------------------------------------------------
        bool endOfWord;
        std::array<std::shared_ptr<TreeNode>, 26> children;
    };
    // Pointer to the root node (has to be after definition of TreeNode class since we're pointing to a TreeNode).
    std::shared_ptr<TreeNode> ptrToRoot;
    // Variable to count the number of words in the tree (use "add" method to increment by 1 for each word, return in the "size" method).
    int numWordsInTree = 0;

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // WordTree MEMBER FUNCTIONS
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Constructor -- will be initialized with a std::array of std::shared_ptrs, each ptr pointing to the: "first 'a' node", "first 'b' node", ...., "first 'z' node"
    //                They will all be set to null to begin with. Implementation in WordTree.cpp
    WordTree();
    // Adds a new word to the tree. If the word already exists there is no duplication
    void add(std::string word);
    // Searches the tree to see if the word is found
    bool find(std::string word);
    // Given the "partial" (or completed) word, returns a std::vector of up to "howMany" predicted words.
    // Requires a breadth-first search of the tree, after the node where the "partial" word ends.
    std::vector<std::string> predict(std::string partial, std::uint8_t howMany);
    // Returns a count of the number of words in the tree.
    std::size_t size();
};
