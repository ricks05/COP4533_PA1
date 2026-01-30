#include "..\src\Matching.h"
#include "..\src\Verifier.h"
#include <iostream>
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

pair<int, int> runTests(int n, Matching& obj) {
    auto startM = chrono::high_resolution_clock::now();
    auto match = obj.matchingEngine();
    auto endM = chrono::high_resolution_clock::now();

    auto elapsedM = chrono::duration_cast<chrono::nanoseconds>(endM - startM);
    cout << "Matcher T(n=" << n << ") = " << elapsedM.count() << " ns" << endl;

    auto hPref = obj.getHPref();
    auto sPref = obj.getSPref();
    Verifier v(n, hPref, sPref, match);

    auto startV = chrono::high_resolution_clock::now();
    v.verifierEngine();
    v.duplicateEngine();
    auto endV = chrono::high_resolution_clock::now();
    auto elapsedV = chrono::duration_cast<chrono::microseconds>(endV - startV);
    cout << "Verifier T(n=" << n << ") = " << elapsedV.count() << " microns\n\n";

    return make_pair((int) elapsedM.count(), (int) elapsedV.count());
}

int main() {
    vector<int> N, Tm, Tv;

    for (int i = 0; i < 14; i++) {
        int n = (int) pow(2, i);
        N.push_back(n);

        auto obj = buildObj(n);

        auto t = runTests(n, obj);
        Tm.push_back(t.first);
        Tv.push_back(t.second);
    }

    ofstream myfile;
    myfile.open("..\\data\\matching_data.csv");
    myfile << "n,T(n)\n";
    for (int i = 0; i < N.size(); i++) {
        myfile << N[i] << "," << Tm[i] << "\n";
    }
    myfile.close();

    myfile.open("..\\data\\verifying_data.csv");
    myfile << "n,T(n)\n";
    for (int i = 0; i < N.size(); i++) {
        myfile << N[i] << "," << Tv[i] << "\n";
    }
    myfile.close();

    // manually run graph.py at this point

    return 0;
}
