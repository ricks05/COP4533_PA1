#include "Matching.h"

vector<int> Matching::matchingEngine() {
    for (int h = 1; h <= n; h++) {
        cout << h << endl;
        if (numMatches == n)
            break;
        if (hMatches[h] != 0 || hTries[h] > n)
            continue;
        int s = hPref[h][hTries[h]++];
        if (sMatches[s] == 0) {
            hMatches[h] = s;
            sMatches[s] = h;
            numMatches++;
        }
        int hPrime = sMatches[s];
        for (int i = 0; i < n ; i++) {
            if (sPref[s][i] == hPrime) {
                break;
            }
            else if (sPref[s][i] == h) {
                hMatches[h] = s;
                sMatches[s] = h;
                hMatches[hPrime] = 0;
                break;
            }
        }
        if (h == n) {
            h = 0;
        }
    }

    return hMatches;
}

int main() {
    int n;
    cin >> n;

    auto h = vector(n+1, vector<int>(n));
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> h[i][j];
        }
    }

    auto s = vector(n+1, vector<int>(n));
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> s[i][j];
        }
    }

    Matching matchObj(n, h, s);
    vector<int> res = matchObj.matchingEngine();

    for (int i = 1; i <= n; i++) {
        cout << i << " " << res[i] << endl;
    }

    return 0;
}
