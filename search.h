//Project 2: Search Engine Project

//Starter code provided by: Professor Ethan Ordentlich, Professor Drishika Dey

/*Description: This program contains different files of urls of different web pages and the text conained within
those files. What the search engine will do is it will parse through those files to check unique words and pages
being processed. Then, based of that processing, depending on the user input, it will return the urls that is
generated within the file. This project uses sets, maps, and file input/output streams, and data processing */

#pragma once

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

//--------------------------------------------------------------------------------------
/**
 cleanToken:
 * Cleans a specific token by:
 * - Removing leading and trailing punctuation
 * - Converting to lowercase
 * If the token has no letters, returns the empty string.
 */


string cleanToken(string s) {

    int strCounter = 0;

    //using a counter, this is going to check if the string coming in contains any letters
    for (int checkInt = 0; checkInt < s.size(); checkInt++){ 
        if (isalpha(s.at(checkInt))){
            strCounter += 1;
        }
    } 

    if (strCounter == 0){ //this indicates that the string has no letters (e.g $$2312!!)
        s = "";
        return s;
    }
    
    else { //this means that there are letters that exist, and the string must be parsed

        //if the iterator reaches a letter or a number for both loops, then it will break out of loop

        for (int i = 0; i < s.size(); i++){ //checks for the punctuation at the beginning
            if (!ispunct(s.at(i))){
                break;
            }
            else {
                s.erase(s.begin() + i);
                i--;
            }
        }

        for (int j = s.size() - 1; j >= 0; j--){ //checks for the puncuation at the end
            if (!ispunct(s.at(j))){
                break;
            }
            else {
                s.erase(s.begin() + j);
                
            }
        }

        //convert all the letters in the string into lowercase
        for (int u = 0; u < s.size(); u++){
            if (isalpha(s.at(u))){
                s.at(u) = tolower(s.at(u));
            }
        }
        return s;
    }
    
}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------

/**
    gatherTokens: Returns a set of the cleaned tokens in the given text.
 */

set<string> gatherTokens(string text) {
    set<string> setTxt; //collects the unique items that exist from the clean string
    string temp; //creates a current empty string

    istringstream iss(text); //taking in a stream for the text

    while (iss >> temp){
        string clean = cleanToken(temp); //clean the string that is being processed

        if (clean != ""){
           
            setTxt.insert(clean); //put the clean string back into the updated set
        }
        
    }
    
    return setTxt;
}

/**
 * buildIndex: Builds the inverted index from the given data file. The existing contents
 * of `index` are left in place.
 */
int buildIndex(string filename, map<string, set<string>>& index) {

    string webURL;
    string webTxt;
    set<string> cleanStr;
    ifstream inFS;
    inFS.open(filename);

    if (!inFS.is_open()){ //take in an ifstream and check if the file exists
        cout << "Invalid filename." << endl;
        return 0;
    }

    set<string> updatedURLS; //final set of all of the urls associated with that file
    int webCount = 0;
    while (!inFS.eof()){
        getline(inFS, webURL); //taking in the URL
        getline(inFS, webTxt); //taking in the text underneath the URL

        cleanStr = gatherTokens(webTxt); //return a set that has been cleaned through gatherTokens and cleanTokens
        
        //it will go through the set and check if there are any empty strings that exist
        for (auto i = cleanStr.begin(); i != cleanStr.end(); i++){ 
 
            if (webURL != ""){
                index[*i].insert(webURL);
                updatedURLS.insert(webURL); //will updated with strings that are not empty
                
            }
            
        }
        
    }

    inFS.close(); //closes the file after it has been complete
    return updatedURLS.size();
}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------

/**
 findQueryMatches:
 * Runs a search query on the provided index, and returns a set of results.
 *
 * Search terms are processed using set operations (union, intersection, difference).
 */
set<string> findQueryMatches(map<string, set<string>>& index, string sentence) {
    
    vector<string> sentVec;
    string temp = "";
    set<string> copyURLS;
    
    //breaks down the sentence and removes all the spaces from the input
    for (int i = 0; i < sentence.size(); i++){
        if (sentence.at(i) == ' ' && temp != ""){ //checks if there is a space or an empty string
            sentVec.push_back(temp);
            temp = "";
        }
        else {
            temp += sentence.at(i);
        }
        
    }
    sentVec.push_back(temp); //push the last word back into the vector


    set<string> othercpyURLS; //final set that will be returned
    set<string> tempURL; //temporary set that will be updated through each command
    set<string> otherSet;

    for (int j = 0; j < sentVec.size(); j++){ //looping through each term in the vector
        if (j == 0){
            if (index.count(cleanToken(sentVec.at(0))) != 0){ //check if the first term exists in the map
                copyURLS = index[cleanToken(sentVec.at(0))]; 
                tempURL = copyURLS;
                
            }
            else { //returns empty set if it does not exist
                tempURL = {};
            }
            
        }
        else{

            if (sentVec[j][0] == '+'){ //is checking the intersection of the two sets

                if (index.count(cleanToken(sentVec[j])) == 0){ //checks if the word after the character does not exist
                    otherSet = {};
                    
                }

                else{
                    otherSet = index[cleanToken(sentVec[j])]; //gets added into another set

                }

                //clearing the set in temporary so that the set intersection can exist
                tempURL.clear();
                set_intersection(othercpyURLS.begin(), othercpyURLS.end(), otherSet.begin(), otherSet.end(), inserter(tempURL, tempURL.begin()));
               
                
            }

            if (sentVec[j][0] == '-'){ //is checking the set difference of the two sets
                if (index.count(cleanToken(sentVec[j])) == 0){ //checks if the word after the character does not exist
                    otherSet = {};
                
                }

                else{
                    otherSet = index[cleanToken(sentVec[j])];

                }

                //clearing the set in temporary so that the set difference can exist
                tempURL.clear();
                set_difference(othercpyURLS.begin(), othercpyURLS.end(), otherSet.begin(), otherSet.end(), inserter(tempURL, tempURL.begin())); 

            }
            
            if (isalpha(sentVec[j][0])){ //is checking the set union of the two sets, meaning no char in front
                
                if (index.count(cleanToken(sentVec[j])) != 0){ //checks if the word after the character does not exist
                     otherSet = index[cleanToken(sentVec[j])];
                }

                else{
                    otherSet = {};

                }
                //clearing the set in temporary so that the set union can exist
                tempURL.clear();
                set_union(othercpyURLS.begin(), othercpyURLS.end(), otherSet.begin(), otherSet.end(), inserter(tempURL, tempURL.begin()));
                
            }
        }
        

        othercpyURLS = tempURL;
    }
    return othercpyURLS;

}

//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
/**
 * Runs the main command loop for the search program
 */
void searchEngine(string filename) {
    string pageURL;
    string pageTxt;
    int filePages = 0;
    int uniqueItems = 0;
    map<string, set<string>> searchMap;
    
    int count = buildIndex(filename, searchMap); //building the index in the map

    //output the url and unique text count in the map after file is processed 
    cout << "Stand by while building index..." << endl;
    cout << "Indexed " << count <<  " pages containing " << searchMap.size() << " unique terms" << endl; 

    string userInput; 
    set<string> findQuery; //set that is returned after the map goes into findQueryMatches

    bool runInput = true;

    do {
        cout << "Enter query sentence (press enter to quit): ";
        getline(cin, userInput); //takes in the user input from the buffer

        if (userInput == "") { //going to check if the user even typed anything at all
            cout << "Thank you for searching!" << endl;
            break;
        }

        set<string> findQuery = findQueryMatches(searchMap, userInput);

        if (findQuery.empty() == false) { //checks if the set returned from the function is not empty
            cout << "Found " << findQuery.size() << " matching pages" << endl; //output number of pages found

            for (const auto &url : findQuery) { //output number of pages that were generated
                cout << url << endl;
            }

        } 
        
        else {
            cout << "Found 0 matching pages" << endl; //this means that no pages were found from the user input
        }
    } while (runInput); //will keep on running until the user decides to break

    //--------------------------------------------------------------------------------------

}