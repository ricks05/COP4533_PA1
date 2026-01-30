#include "..\src\Matching.h"
#include <cmath>
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>

Matching buildObj(int n) {
    random_device rd;
    mt19937 gen(rd());

    auto h = vector(n+1, vector<int>(n+1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            h[i][j] = j;
        }
        shuffle(h[i].begin() + 1, h[i].end(), gen);
    }

    auto s = vector(n+1, vector<int>(n+1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            s[i][j] = j;
        }
        shuffle(s[i].begin() + 1, s[i].end(), gen);
    }

    // keep track of unmatched hospitals
    unordered_set<int> u;
    for (int i = 1; i <= n; i++) {
        u.insert(i);
    }

    Matching obj(n, h, s, u);
    return obj;
}

int runTest(int n, Matching& obj) {
    auto start = chrono::high_resolution_clock::now();

    obj.matchingEngine();

    auto end = chrono::high_resolution_clock::now();

    auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start);
    cout << "T(n=" << n << "): " << elapsed.count() << " ns" << endl;
    return (int) elapsed.count();
}

int main() {
    vector<int> N, T;

    for (int i = 0; i < 14; i++) {
        int n = (int) pow(2, i);
        N.push_back(n);

        auto obj = buildObj(n);

        auto t = runTest(n, obj);
        T.push_back(t);
    }

    ofstream myfile;
    myfile.open("..\\data\\matching_data.csv");
    myfile << "n,T(n)\n";
    for (int i = 0; i < N.size(); i++) {
        myfile << N[i] << "," << T[i] << "\n";
    }
    myfile.close();

    // manually run graph.py at this point

    return 0;
}
