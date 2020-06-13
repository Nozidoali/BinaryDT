#ifndef BINARY_DECISION_TREE_H
#define BINARY_DECISION_TREE_H

#include "Cmdline.h"
#include <fstream>
#include <cassert>
#include <set>
#include <cmath>

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
struct Node {
    Node * left, * right;
    int literal; // -1 if non split
    Logic logic;
    set<int> entries;
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
    Node * root;
    int size;
    Tree(): root(nullptr) {}
};

/**
 * Truth Table of Data Set
 */
struct Data {
    int numInput, numOutput, size;
    bool * input, * output;
    Data(): input(nullptr), output(nullptr) {}
};

struct Manager {
    Tree * dtree;
    Data * data;
    Manager(): dtree(nullptr), data(nullptr) {}
};

Manager * Man_Init ();

double Entropy ( double count[2] );

void Nod_TrainDT ( Node * node, Data * data );
int Nod_WriteAag ( Node * node, ostream & fout );

void Tre_WriteAag ( Tree * tree, ostream & fout );
void Tre_TrainDT ( Tree * tree, Data * data );

void Dat_LoadPla ( Data * data, istream & fin );
void Dat_Free ( Data * data );
bool Dat_LookUp ( Data * data, int entry, int index );

void Man_LoadFile ( Manager * man, string filename );
void Man_TrainDT ( Manager * man );
void Man_TestDT ();
void Man_WriteAag ( Manager * man, string filename );
void Man_Free ( Manager * man );


#define ForEachInputRec( data ) \
    for ( bool ** input = data->input; input < data->input + data->size; input ++ )

#define ForEachLit( input ) \
    for ( bool * lit = input; lit < input + data->numInput; lit ++ )

#define ForEachIndex( data ) \
    for ( int i = 0; i < data->numInput; i ++ )

#endif