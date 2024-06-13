# SpellChecker STL
Enhance your software with a robust Spell Checker! This C++ project leverages Trie data structure for lightning-fast word lookups and employs Levenshtein Distance algorithm for precise typo corrections. Perfect for optimizing text inputs and enhancing user experience. Explore and integrate today!

# Spell Checker using Trie and Levenshtein Distance

Enhance your software applications with a powerful Spell Checker implemented in C++! This project utilizes advanced data structures and algorithms to provide accurate word suggestions and typo corrections.

## Features

- **Trie Data Structure:** Efficient storage for quick prefix-based searches.
- **Levenshtein Distance Algorithm:** Calculates word similarity for accurate suggestions.
- **File Handling:** Reads words from external files for comprehensive spell checking.
- **Performance Optimized:** Designed for fast response times with large datasets.

## Getting Started

To integrate the Spell Checker into your project, follow these simple steps:
```cpp
#include "SpellChecker.h"
#include <iostream>

int main() {
    Trie trie;
    readWordsFromFile("wordsFILE.txt", trie);

    std::string input;
    std::cout << "Enter a word or phrase: ";
    std::getline(std::cin, input);

    std::string nearestWord = findNearestWord(input, trie);
    std::cout << "Nearest word: " << nearestWord << std::endl;

    return 0;
}
```
