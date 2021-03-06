#ifndef BINARY_DECISION_TREE_H
#define BINARY_DECISION_TREE_H

#include "Cmdline.h"
#include "Format.h"
#include <fstream>
#include <cassert>
#include <set>
#include <cmath>

#define MAX_DEPTH 100
#define MAX_GAIN make_pair(0,1)

using namespace std;
using namespace cmdline;

enum Logic {
    MUX,
    XOR,
    CONST0,
    CONST1,
    EMPTY
};

enum Mode {
    TRAIN,
    VALID,
    TEST
};

/**
 * Node in Binary Decision Tree
 */
class Node {

public:
    Node * left, * right;
    int literal; // -1 if non split
    int depth;   // 
    Logic logic;
    set<int> entries;
    set<int> indices;
    double * count;
    Node(): left(nullptr), right(nullptr) { 
        count = new double[2]; 
        count[0] = count[1] = 0;
    }
};

/**
 * Binary Decision Tree
 */
struct Tree {

public:
    Node * root;
    int size;
    Tree(): root(nullptr) {}
};

/**
 * Truth Table of Data Set
 */
class Data {

public:
    int numInput, numOutput, size;
    bool * input, * output;
    Data(): input(nullptr), output(nullptr) {}
};

/**
 * Manager: Perform Training and Validation on data
 */
class Manager {

public:
    Tree * dtree;
    Data * data;
    string name;
    Manager(): dtree(nullptr), data(nullptr), name("why") {}
};

Manager * Man_Init ();

double Entropy ( double count[2] );

/* ================================= Node ================================== */

int         Nod_WriteAag    ( Node * node, AIG_Format * fout );
int         Nod_WriteBlif   ( Node * node, ostream & fout );
void        Nod_TrainDT     ( Node * node, Data * data );

/* ================================= Tree ================================== */

void        Tre_WriteAag    ( Tree * tree, AIG_Format * fout );
void        Tre_WriteBlif   ( Tree * tree, ostream & fout );
void        Tre_TrainDT     ( Tree * tree, Data * data );

/* ================================= Data ================================== */

void        Dat_LoadPla     ( Data * data, istream & fin );
void        Dat_Free        ( Data * data );
bool        Dat_LookUp      ( Data * data, int entry, int index );

/* =============================== Manager ================================= */

void        Man_LoadFile    ( Manager * man, string filename );
void        Man_WriteAag    ( Manager * man, string filename );
void        Man_TrainDT     ( Manager * man );
double      Man_ValidDT     ( Manager * man );
void        Man_WriteBlif   ( Manager * man, string filename );
void        Man_Free        ( Manager * man );


#define ForEachInputRec( data ) \
    for ( bool ** input = data->input; input < data->input + data->size; input ++ )

#define ForEachLit( input ) \
    for ( bool * lit = input; lit < input + data->numInput; lit ++ )

#define ForEachIndex( data ) \
    for ( int i = 0; i < data->numInput; i ++ )

#endif