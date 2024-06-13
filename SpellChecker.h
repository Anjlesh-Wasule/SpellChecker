#ifndef SPELLCHECKER_H
#define SPELLCHECKER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include<limits.h>
 
using namespace std;

// Trie node definition
struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

// Trie class definition
class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    //  Insert a word into the Trie
    void insert(const string &word){
        TrieNode* node = root;
        for(char ch : word){
            if(node->children.find(ch) == node->children.end()){
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch]; 
        }
        node->isEndOfWord = true;
    }

    // Find words with a given prefix
    vector<string> findWordsWithPrefix(const string &prefix)const{
        TrieNode* node = root;
        vector<string> results; // one or more words can be there

        for(char ch : prefix){
            if(node->children.find(ch) == node->children.end()){
                // no such words found in map with given prefix
                return results;
            }
            node = node->children[ch];
        }
        findAllWords(node, prefix, results);
        return results;
    }

private:
    TrieNode* root;
    // Helper function to find all words starting from a given node
    void findAllWords(TrieNode* node, const string &prefix, vector<string> &results)const{
        if(node->isEndOfWord){
            results.push_back(prefix);
        }

        for(auto &pair : node->children){
            findAllWords(pair.second, prefix + pair.first, results);
        }
    }
};

// Function to read words from a file and insert them into a Trie
void readWordsFromFile(const string &filename, Trie &trie){
    ifstream file(filename);
    if(file.is_open()){
        string word;
        while (file >> word)
        {
            trie.insert(word);  //Insert each word into the Trie
        }

        file.close();
    }
    else{
        cout << "Unable to Open the file " << filename << endl;
    }
}

// Function to calculate the Levenshtein distance between two words
int levenshteinDistance(const string &s1,const string &s2){
    int len1 = s1.size();
    int len2 = s2.size();
    vector<vector<int>> d(len1+1, vector<int>(len2 + 1));

    for (int i = 0; i <= len1; ++i) d[i][0] = i;
    for (int j = 0; j <= len2; ++j) d[0][j] = j;

    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; ++j) {
            d[i][j] = min(
                d[i - 1][j] + 1,
                min(
                    d[i][j - 1] + 1,
                    d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1)
                )
            );
        }
    }
    return d[len1][len2];
}

// Function to find the nearest word using Levenshtein distance
string findNearestWord(const string &input,const Trie &trie){
    vector<string> allWords = trie.findWordsWithPrefix("");
    int minDistance = INT_MAX;
    string nearestWord;

    for (const auto &word : allWords) {
        int distance = levenshteinDistance(input, word);
        if (distance < minDistance) {
            minDistance = distance;
            nearestWord = word;
        }
    }

    return nearestWord;
}
#endif // SPELLCHECKER_H