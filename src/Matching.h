#include <vector>
#include <iostream>
#pragma once
using namespace std;

class Matching {
    int n;
    vector<vector<int>> hPref, sPref; // each row represents a hospital/student, each column is that entity's preferred student/hospital
    vector<int> hMatches, sMatches, hTries; // each index is a hospital/student, where its elements are their matched student/hospital
    int numMatches;
public:
    Matching(int n, vector<vector<int>>& h, vector<vector<int>>& s)
        : n(n), hPref(h), sPref(s), hMatches(n+1, 0), sMatches(n+1, 0),
          hTries(n+1, 0), numMatches(0) {}
    vector<int> matchingEngine();
};