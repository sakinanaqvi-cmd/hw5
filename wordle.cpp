#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(
    std::string& curr,
    const std::string& floating,
    const std::set<std::string>& dict,
    std::set<std::string> finalVals,
    int ind) {
      //BC: at the end of word
      if(ind == curr.size()) {
        std::string floating2 = floating;
        std::string check = curr;

        for(size_t i = 0; i < floating2.size(); ++i) {
          char c = floating2[i];
          size_t position = check.find(c);
          if(position == std::npos) return;
          check[position] = '*';
        }

        if(dict.count(curr)) finalVals.insert(curr);
        return;
      }
      if(curr[ind] != '_') wordleHelper(curr, floating, dict, finalVals, ind + 1);
      else {
        std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
        for(size_t i = 0; i < alphabet.size(); ++i) {
          curr[ind] = alphabet[i];
          wordleHelper(curr, floating, dict, finalVals, ind + 1);
        }
        curr[ind] = '_';
      }

}

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    std::set<std::string> finalVals;
    std::string curr = in;

    wordleHelper(curr, floating, dict, finalVals, 0);
    return finalVals;

}

// Define any helper functions here
