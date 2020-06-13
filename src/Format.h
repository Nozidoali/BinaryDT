#ifndef FORMAT_H
#define FORMAT_H

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

class Formater {

public:
    string filename;
    virtual void WriteFile() = 0;
    virtual void ReadFile()  = 0;
};

class AIG_Format : public Formater {


public:
    struct Node {
        int left, right, out;
    };
    vector<int> input;     // id of inputs
    vector<int> output;    // id of outputs
    vector<Node> nodes;    // set of declarations
    void WriteFile();
    void ReadFile() {};
    void Add( int _left, int _right, int _out );
};

#endif