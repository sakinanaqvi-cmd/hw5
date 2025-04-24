#ifndef RECCHECK
#include <iostream>
#include <algorithm>
#include <string>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;

void wordleHelper(
    std::string curr,
    std::string floating,
    const std::set<std::string>& dict,
    std::set<std::string>& finalVals,
    size_t ind,
    size_t remDash);

std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    std::set<std::string> finalVals;
    size_t remDash = count(in.begin(), in.end(), '-'); // Precompute dashes
    wordleHelper(in, floating, dict, finalVals, 0, remDash);
    return finalVals;
}

void wordleHelper(
    std::string curr,
    std::string floating,
    const std::set<std::string>& dict,
    std::set<std::string>& finalVals,
    size_t ind,
    size_t remDash)
{
    //where no floating and the word is ended
    if (ind == curr.size()) {
        if (dict.find(curr) != dict.end() && floating.empty()) finalVals.insert(curr);
        return;
    }

    //handles if char is not dash and within bounds
    if (curr[ind] != '-' && curr.size() > ind) {
        wordleHelper(curr, floating, dict, finalVals, ind + 1, remDash);
        return;
    }

    if (floating.size() + 26 < remDash) {
        return; 
    }

    //fill dashes with floating
     for (size_t i = 0; i < floating.size(); i++) {
         char c = floating[i];
         //replace dash at the current
         curr[ind] = c;

         std::string floatTemp = floating;
         //remove used letters from floating 
         floatTemp.erase(i, 1);

         wordleHelper(curr, floatTemp, dict, finalVals, ind + 1, remDash - 1);
         //backtrack
         curr[ind] = '-';
     }

    //if dashes are more than floating, fill dash with other letters
    string alph = "abcdefghijklmnopqrstuvwxyz"; 
    if (floating.size() < remDash) {
        for (char c : alph) {
            curr[ind] = c;
            wordleHelper(curr, floating, dict, finalVals, ind + 1, remDash - 1);
            //backtrack
            curr[ind] = '-';
        }
    }
}
