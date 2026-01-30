#include <vector>
#include <unordered_set>
#pragma once
using namespace std;

class Verifier {
    int n;  // number of hospital/students
    vector<vector<int>> hPref, sPref; // each row represents a hospital/student, each column is that entity's preferred student/hospital
    vector<int> matchList;  // result of the matching algorithm
public:
    Verifier(int n, vector<vector<int>>& h, vector<vector<int>>& s, vector<int>& m)
            : n(n), hPref(h), sPref(s), matchList(m) {}
    bool verifierEngine();  // returns a bool indicating if matching is stable
    bool duplicateEngine();  // returns a bool indicating if matching has no duplicates
};
