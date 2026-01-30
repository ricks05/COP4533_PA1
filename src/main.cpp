#include "Matching.h"
#include "Verifier.h"
#include <fstream>
#include <iostream>

int main() {
    ifstream fin("../io_files/ExampleInput");
    ofstream fout("../io_files/ExampleOutput");

    if (!fin) {
        cerr << "Failed to open ExampleInput file\n";
        return 1;
    }

    if (!fout) {
        cerr << "Failed to open ExampleOutput file\n";
        return 1;
    }

    int n;
    fin >> n;

    // each row is a hospital, each column is a student (in descending preference order)
    // first row are zeros (for sake of indexing)
    auto h = vector(n+1, vector<int>(n+1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            fin >> h[i][j];
        }
    }

    // each row is a student. for columns, indexes represent hospitals and values represent their rank
    // first row and first column are zeros (for sake of ease of indexing)
    auto s = vector(n+1, vector<int>(n+1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int curH;
            fin >> curH;
            s[i][curH] = j;
        }
    }

    // keep track of unmatched hospitals
    unordered_set<int> u;
    for (int i = 1; i <= n; i++) {
        u.insert(i);
    }

    // running the matching engine
    Matching matchObj(n, h, s, u);
    vector<int> res = matchObj.matchingEngine();

    for (int i = 1; i <= n; i++) {
        fout << i << " " << res[i] << endl;
    }

    // make Verifier object and pass through n, hospital preference, student preferences, and matching result
    Verifier verifierObj(n, h, s, res);
    // run verifier functions
    bool stability = verifierObj.verifierEngine();
    bool validity = verifierObj.duplicateEngine();

    // write output based on validity and stability
    if(stability && validity)
        fout << "VALID STABLE";
    else if(!stability && !validity)
        fout << "INVALID UNSTABLE";
    else if(!stability)
        fout << "UNSTABLE";
    else
        fout << "INVALID";

    return 0;
}
