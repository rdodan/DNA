//
//  application.cpp
//

#include <iostream>
#include <fstream>
#include "dna.h"
#include <vector>
#include <map>
using namespace std;

// check if the vector created matches one of the map's value
// if so return true, else false
bool checkMatch( map<string, vector<int>>& mp, vector<int> &v) {
    for (auto &e : mp) {
        if (mp[e.first] == v) {
            cout << "DNA match: " << e.first << endl;
            return true;
        }
    }
    return false;
}
// gets the counter 
void checkObject(string databasefile, string dnafile, map<string, vector<int>>& mp, vector<int> &v) {
    ifstream myFile(databasefile);
    ifstream mySecond(dnafile);
    string objString;
    int count = 0;
    getline(mySecond, objString);  // gets first line from database file
    dna d1(objString);  // creates the linked list
    dna copyd1(d1);
    string input;
    string target;
    getline(myFile, input, '\n');
    input = input + ',';  // parse it to get rid of "name"
    size_t pos = input.find(",");
    input = input.substr(pos+1, input.size() - pos);

    // set a counter and increment by 1 everytime
    // the splice function is true
    while (!input.empty()) {
        size_t pos = input.find(",");
        target = input.substr(0, pos);
        input = input.substr(pos+1, input.size() - pos);
        dna d2(target);  // create the object
        while (copyd1.splice(d2) == true) {
            count ++;
        }
        // push the counter into the vector 
        v.push_back(count);
        copyd1.clear();
        copyd1 = d1;
        count = 0;
    }
}

// function that build the map 
void buildMap(string databasefile, map<string, vector<int>>& mp) {
    // read from the file
    ifstream myFile(databasefile);
    string input;
    getline(myFile, input, '\n');  // get first line
    string eachLine;
    string temp;  // holds the temp 
    vector<int> vect;
    string key;
    while (getline(myFile, eachLine, '\n')) {
        eachLine = eachLine + ',';
        size_t pos = eachLine.find(",");
        key = eachLine.substr(0, pos);
        eachLine = eachLine.substr(pos+1, eachLine.size() - pos);
        while (!eachLine.empty()) {  // parse until line ends
            size_t pos = eachLine.find(",");
            vect.push_back(stoi(eachLine.substr(0, pos)));
            eachLine = eachLine.substr(pos+1, eachLine.size() - pos);
        }
        mp[key] = vect;
        vect.clear();  // clear the vector 
    }
}



int main() {
    // create DNA object
    string databasefile;
    string dnafile;
    ifstream myFile;
    ifstream myDnaFile;
    map<string, vector<int>> mp;

    cout << "Welcome to the DNA Profiling App!" << endl;
    cout << "Enter database file: ";
    cin >> databasefile;

    cout << "Enter dna file: ";     
    cin >> dnafile;
    
    vector<int> valueDB;
    
    cout << "Searching database..." << endl;
    buildMap(databasefile,mp);
    checkObject(databasefile, dnafile, mp, valueDB);
    if (checkMatch(mp, valueDB) == false) {
        cout << "No match." << endl;
    }
    
    
    return 0;
}
