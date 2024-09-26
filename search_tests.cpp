#include <gtest/gtest.h>

#include "search.h"
#include "tests/build_index.h"
#include "tests/clean_token.h"
#include "tests/find_query_matches.h"
#include "tests/gather_tokens.h"

TEST(CleanToken, normalCleaning) {
    map<string, set<string>> tests;
    tests["telephone"].insert("!!!!Telephone...");
    tests["cs251"].insert("^^^^^************CS251+++++++++");
    tests["testing"].insert("???????testing%$#%$#%##%");

    testCleanToken(tests);
}

TEST(CleanToken, withPunctInMiddle) {
    map<string, set<string>> tests;
    tests["hi-miss"].insert("Hi-Miss");
    tests["cs251**is**awesome"].insert("&^&%&%$%CS251**is**awesome&^*^*%^*^");
    tests["karat+magic"].insert("^^$^%^$^%^$Karat+Magic");
    tests["find-me"].insert("find-me.......");

    testCleanToken(tests);
}

TEST(GatherTokens, AtTheBegin) {
    string text = "        a ray of sunshine";
    set<string> expected = {"a", "ray", "of", "sunshine"};
    set<string> studentResult = gatherTokens(text);

    string testFeedback = "gatherTokens(\"" + text + "\") incorrect\n";

    EXPECT_EQ(expected, studentResult) << testFeedback;
}

TEST(GatherTokens, InTheMid) {
    string text = "a delightful       morning      I must say";
    set<string> expected = {"a", "delightful", "morning", "i", "must", "say"};
    set<string> studentResult = gatherTokens(text);

    string testFeedback = "gatherTokens(\"" + text + "\") incorrect\n";

    EXPECT_EQ(expected, studentResult) << testFeedback;
}

TEST(GatherTokens, AtTheEnd) {
    string text = "just looking radiant         ";
    set<string> expected = {"just", "looking", "radiant"};
    set<string> studentResult = gatherTokens(text);

    string testFeedback = "gatherTokens(\"" + text + "\") incorrect\n";

    EXPECT_EQ(expected, studentResult) << testFeedback;
}

TEST(BuildIndex, TinyTxt) {
    string filename = "tiny.txt";
     int expectedCount = 10;
    map<string, set<string>> expected = {
        {"eggs", {"www.shoppinglist.com"}},
        {"milk", {"www.shoppinglist.com"}},
        {"fish", {"www.shoppinglist.com", "www.dr.seuss.net"}},
        {"bread", {"www.shoppinglist.com"}},
        {"cheese", {"www.shoppinglist.com"}},
        {"red", {"www.rainbow.org", "www.dr.seuss.net"}},
        {"green", {"www.rainbow.org"}},
        {"orange", {"www.rainbow.org"}},
        {"yellow", {"www.rainbow.org"}},
        {"blue", {"www.rainbow.org", "www.dr.seuss.net"}},
        {"indigo", {"www.rainbow.org"}},
        {"violet", {"www.rainbow.org"}},
        {"one", {"www.dr.seuss.net"}},
        {"two", {"www.dr.seuss.net"}},
        {"i'm", {"www.bigbadwolf.com"}},
        {"not", {"www.bigbadwolf.com"}},
        {"trying", {"www.bigbadwolf.com"}},
        {"to", {"www.bigbadwolf.com"}},
        {"eat", {"www.bigbadwolf.com"}},
        {"you", {"www.bigbadwolf.com"}},
    };
    map<string, set<string>> studentIndex;
    int studentNumProcesed = buildIndex(filename, studentIndex);
    cout << "Student Num Processed: " << studentNumProcesed << endl;
    string indexTestFeedback = "buildIndex(\"" + filename + "\", ...) index incorrect\n";
    EXPECT_EQ(expected, studentIndex) << indexTestFeedback;

    string retTestFeedback = "buildIndex(\"" + filename + "\", ...) return value incorrect\n";
    EXPECT_EQ(4, studentNumProcesed) << retTestFeedback;
    
}

TEST(BuildIndex, InvalidTxt) {
    string filename = "blah.txt";
    map<string, set<string>> expected = {};
    map<string, set<string>> studentIndex;
    int studentNumProcesed = buildIndex(filename, studentIndex);
    cout << "Student Num Processed: " << studentNumProcesed << endl;
    string indexTestFeedback = "buildIndex(\"" + filename + "\", ...) index incorrect\n";
    EXPECT_EQ(expected, studentIndex) << indexTestFeedback;

    string retTestFeedback = "buildIndex(\"" + filename + "\", ...) return value incorrect\n";
    EXPECT_EQ(0, studentNumProcesed) << retTestFeedback;
}

TEST(FindQueryMatches, firstTerm) {
    map<string, set<string>> INDEX = {
    {"hello", {"example.com", "uic.edu"}},
    {"there", {"example.com"}},
    {"according", {"uic.edu"}},
    {"to", {"uic.edu"}},
    {"all", {"example.com", "uic.edu", "random.org"}},
    {"known", {"uic.edu"}},
    {"laws", {"random.org"}},
    {"of", {"random.org"}},
    {"aviation", {"random.org"}},
    {"a", {"uic.edu", "random.org"}},
   };

    set<string> expected;

    expected = {"example.com", "uic.edu", "random.org"};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "alliance all"));

    expected = {};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "at"));
    
}

TEST(FindQueryMatches, LaterTerm) {
    map<string, set<string>> INDEX = {
    {"hello", {"example.com", "uic.edu"}},
    {"there", {"example.com"}},
    {"according", {"uic.edu"}},
    {"to", {"uic.edu"}},
    {"all", {"example.com", "uic.edu", "random.org"}},
    {"known", {"uic.edu"}},
    {"laws", {"random.org"}},
    {"of", {"random.org"}},
    {"aviation", {"random.org"}},
    {"a", {"uic.edu", "random.org"}},
   };

    set<string> expected;

    expected = {};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "aviation +alien"));

    expected = {"random.org"};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "laws allegory"));
    
    expected = {"example.com", "uic.edu"};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "hello -trailer"));
}


TEST(CleanToken, ExampleEmptyTest) {
    cout << "Hi! This shows up in the terminal." << endl;
}