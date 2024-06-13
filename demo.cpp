#include<iostream>
#include"SpellChecker.h"
using namespace std;

int main(){
    Trie trie;

    // Read words from file and insert them into the Trie
    readWordsFromFile("words.txt", trie);

    // Get user input
    string inputWord;
    cout << "Enter a word to check: ";
    getline(cin, inputWord); // Use getline to handle spaces

    // Find and display the nearest word
    string nearestWord = findNearestWord(inputWord, trie);
    cout << "Did you mean: " << nearestWord << "?" << endl;

    return 0;
}