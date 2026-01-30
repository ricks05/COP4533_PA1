#include "Verifier.h"

bool Verifying::verifyingEngine() {
    for(int i = 1; i < matchList.size(); i ++) {  // run through every match in the list of matches
        for(int j = n; j >= 1; j--) {  // starting from the end of the cur hospital's preference list
            // find the position of the current hospital's matched student
            if(hPref.at(i).at(j) == (matchList.at(i))) {
                // run through every possible preference that the hospital prefers over its current match
                for(int p = j-1; p >= 1; p--) {
                    int curHospital;  // holds the matched hospital match of the greater student pref
                    // run through list of matches to find currently matched hospital to preferred student
                    for(int l = 1; l < matchList.size(); l++) {
                        if(matchList.at(l) == hPref.at(i).at(p)) {
                            curHospital = l;
                            break;
                        }
                    }
                    // go through student's preference list
                    for(int k = n; k >= 1; k--) {
                        // if original hospital shows up first, it so not preferred over current match, therefore stable
                        if(sPref.at(p).at(k) == i)
                            break;
                        // if current matched hospital shows up first, both student and hospital prefer each other,
                        // therefore unstable
                        else if (sPref.at(p).at(k) == curHospital)
                            return false;
                    }
                }
                break;
            }
        }
    }
    return true;  // no unstable matches, therefore stable
}

bool Verifying::duplicateEngine() {
    unordered_set<int> students;  // set to hold all students
    for(int match : matchList) {  // goes through every student
        if(students.find(match) == students.end())  // tries to find if student has already been assigned
            students.insert(match);  // insert students if not previously
        else
            return false;  // student has been assigned twice, duplicate, therefore invalid matching
    }
    return true;  // no duplicate students or hospitals
}