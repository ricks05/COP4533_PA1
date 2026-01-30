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
