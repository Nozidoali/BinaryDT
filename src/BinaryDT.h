#ifndef BINARY_DECISION_TREE_H
#define BINARY_DECISION_TREE_H

#include "Cmdline.h"
#include <fstream>
#include <cassert>

using namespace std;
using namespace cmdline;

enum Logic {
    MUX,
    XOR
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
    int index;
    Node(): left(nullptr), right(nullptr) {}
};

/**
 * Binary Decision Tree
 */
struct Tree {
    Node * root;
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

void Dat_LoadPla ( Data * data, istream & fin );
void Dat_Free ( Data * data );

struct Manager {
    Tree * dtree;
    Data * data;
};

Manager * Man_Init ();
void Man_LoadFile ( Manager * man, string filename );
void Man_TrainDT ();
void Man_TestDT ();
void Man_WriteAag ();
void Man_Free ( Manager * man );


#endif