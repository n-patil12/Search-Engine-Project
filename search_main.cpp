#include <iostream>
#include <string>

#include "search.h"

using namespace std;

int main() {

    // // cout << cleanToken("$$$2132") << endl;
    string filename;
    getline(cin, filename);

    // This will not work until we're done with the project!
    searchEngine(filename);
    
    return 0;

    // string filename = "tinier.txt";
    // map<string, set<string>> expected = {
    //     {"to", {"www.example.com", "www.otherexample.com"}},
    //     {"be", {"www.example.com", "www.otherexample.com"}},
    //     {"ora", {"www.example.com"}},
    //     {"not", {"www.example.com"}},
    //     {"want", {"www.otherexample.com"}},
    //     {"free", {"www.otherexample.com"}},
    // };
    // map<string, set<string>> studentIndex;
    // int studentNumProcesed = buildIndex(filename, studentIndex);
    // cout << "Student Num Processed: " << studentNumProcesed << endl;
    // return 0;

    // map<string, set<string>> INDEX = {
    //     {"hello", {"example.com", "uic.edu"}},
    //     {"there", {"example.com"}},
    //     {"according", {"uic.edu"}},
    //     {"to", {"uic.edu"}},
    //     {"all", {"example.com", "uic.edu", "random.org"}},
    //     {"known", {"uic.edu"}},
    //     {"laws", {"random.org"}},
    //     {"of", {"random.org"}},
    //     {"aviation", {"random.org"}},
    //     {"a", {"uic.edu", "random.org"}},
    // };

    // set<string> testURL = findQueryMatches(INDEX, "all +all -all all");
    //return 0;
}
