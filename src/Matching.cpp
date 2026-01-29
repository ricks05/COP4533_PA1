#include "Matching.h"

vector<int> Matching::matchingEngine() {
    while (!unmatched.empty()) {
        int h = *unmatched.begin();
        if (hTries[h] >= n) {
            unmatched.erase(h);
            continue;
        }
        int s = hPref[h][++hTries[h]]; // hTries will read [1, n]
        if (sMatches[s] == 0) {
            hMatches[h] = s;
            unmatched.erase(h);

            sMatches[s] = h;
        }
        else {
            int hPrime = sMatches[s];
            if (sPref[s][h] < sPref[s][hPrime]) { // lower number == higher preference
                hMatches[h] = s;
                unmatched.erase(h);

                sMatches[s] = h;

                hMatches[hPrime] = 0;
                unmatched.insert(hPrime);
            }
        }
    }

    return hMatches;
}

int main() {
    int n;
    cin >> n;

    // each row is a hospital, each column is a student (in descending preference order)
    // first row are zeros (for sake of indexing)
    auto h = vector(n+1, vector<int>(n+1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> h[i][j];
        }
    }

    // each row is a student. for columns, indexes represent hospitals and values represent their rank
    // first row and first column are zeros (for sake of ease of indexing)
    auto s = vector(n+1, vector<int>(n+1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int curH;
            cin >> curH;
            s[i][curH] = j;
        }
    }



    unordered_set<int> u;
    for (int i = 1; i <= n; i++) {
        u.insert(i);
    }

    Matching matchObj(n, h, s, u);
    vector<int> res = matchObj.matchingEngine();

    for (int i = 1; i <= n; i++) {
        cout << i << " " << res[i] << endl;
    }

    return 0;
}
