/*****************************************************************************/
/* Engine.h: All the commands and operation act on logic network             */
/*     two method need to be implemented. Readfile() and Writefile().        */
/*                                                                           */
/* class Manager                                                             */
/*      class AIG_Format                                                     */
/*      class PLA_Format                                                     */
/*      class BLIF_Format                                                    */
/*****************************************************************************/
#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <set>
#include <unordered_set>
#include <vector>
#include <cmath>

#include "Format.h"

using namespace std;

class Manager {

public:
    string command;             // type of task
    vector<string> arguments;   // allow the manager to take arguments
    string InputFileName;       // Input file name
    string OutputFileName;      // Output file name
    Manager( string input, string output, string command ) :
        InputFileName(input), OutputFileName(output), command(command){};
    void ExecuteCommand(){};
};

/**
 * DT_Manager: Decision Tree Training
 */
class DT_Manager : public Manager {
public:
    void ExecuteCommand ();
};

/**
 * RT_Manager: Redundancy Test
 */
class RT_Manager : public Manager {
public:
    void ExecuteCommand ();
};

/**
 * NT_Manager:  Noise Test
 */
class NT_Manager : public Manager {
public:
    void ExecuteCommand ();
};


static Manager * manager;
void Run( string input, string output, string command );


#endif