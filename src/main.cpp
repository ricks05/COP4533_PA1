#include "Matching.h"
#include "Verifier.h"
#include <fstream>
#include <iostream>

int main() {
    ifstream fin("../io_files/ExampleInput");  // open file for input
    ofstream fout("../io_files/ExampleOutput");  // open file for output

    if (!fin) {  // check if file opened successfully
        cerr << "Failed to open ExampleInput file\n";
        return -1;
    }

    if (!fout) {  // check if file opened successfully
        cerr << "Failed to open ExampleOutput file\n";
        return -1;
    }

    int n;
    if(!(fin >> n) || n < 1) {
        fout << "INVALID - Must indicated a positive N";
        return -1;
    }

    // each row is a hospital, each column is a student (in descending preference order)
    // first row are zeros (for sake of indexing)
    auto h = vector(n+1, vector<int>(n+1));
    for (int i = 1; i <= n; i++) {
        unordered_set<int> seen;
        for (int j = 1; j <= n; j++) {
            int x;
            if(!(fin >> x)) {
                fout << "INVALID - There must be N rows of hospital and student preferences";
                return -1;
            }
            if(x < 1) {
                fout << "INVALID - No negative preferences";
                return -1;
            }
            if(x > n) {
                fout << "INVALID - Preferences cannot exceed N";
                return -1;
            }
            if(seen.count(x)) {
                fout << "INVALID - No duplicate preferences";
                return -1;
            }
            seen.insert(x);
            h[i][j] = x;
        }
    }

    // each row is a student. for columns, indexes represent hospitals and values represent their rank
    // first row and first column are zeros (for sake of ease of indexing)
    auto s = vector(n+1, vector<int>(n+1));
    for (int i = 1; i <= n; i++) {
        unordered_set<int> seen;
        for (int j = 1; j <= n; j++) {
            int curH;
            if(!(fin >> curH)) {
                fout << "INVALID - There must be an equal N rows of hospital and student preferences";
                return -1;
            }
            if(curH < 1) {
                fout << "INVALID - No negative preferences";
                return -1;
            }
            if(curH > n) {
                fout << "INVALID - Preferences cannot exceed N";
                return -1;
            }
            if(seen.count(curH)) {
                fout << "INVALID - No duplicate preferences (There must be n rows and columns";
                return -1;
            }
            seen.insert(curH);
            s[i][curH] = j;
        }
    }

    // "(i.e., equal number of hospitals and students)"
    if(fin >> n) {
        fout << "INVALID - Must have balanced hospitals and students";
        return -1;
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
    vector<int> stability = verifierObj.verifierEngine();
    bool validity = verifierObj.duplicateEngine();

    // write output based on validity and stability
    if(stability[0] && validity)
        fout << "VALID STABLE";
    else if(stability[0] && !validity)
        fout << "INVALID UNSTABLE - (" << stability[1] << "," << stability[2] << ") AND Duplicate student match";
    else if(stability[0])
        fout << "UNSTABLE (" << stability[1] << "," << stability[2] << ")";
    else
        fout << "INVALID - Duplicate student matched";

    return 0;
}
