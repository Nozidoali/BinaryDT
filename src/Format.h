/*****************************************************************************/
/* Format.h: All the I/O Format of logic network. Note that for each format, */
/*     two method need to be implemented. Readfile() and Writefile().        */
/*                                                                           */
/* class Formater                                                            */
/*      class AIG_Format                                                     */
/*      class PLA_Format                                                     */
/*      class BLIF_Format                                                    */
/*****************************************************************************/

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
    Formater(){};
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

class PLA_Format : public Formater {

public:
    struct Entry {
        vector<bool> inputs;    // input value
        vector<bool> outputs;   // output value
    };
    vector<Entry> data;         // data
    void WriteFile() {};
    void ReadFile();

};

#endif