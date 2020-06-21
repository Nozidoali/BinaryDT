#include "Engine.h"

void Search ( PLA_Format * input, int index, int * stats ) {
    if ( index == input->data[0].inputs.size() ) {
        return;
    }

}

void RD_Manager :: ExecuteCommand () {

    // take pla as input and aag as output
    PLA_Format * input  = new PLA_Format;
    AIG_Format * output = new AIG_Format;
    input->filename = InputFileName;
    output->filename = OutputFileName;

    input->ReadFile();

    int numInput = input->data[0].inputs.size();
    int size = input->data.size();

    int memory [ 1<<16 ];
    int count[2] = {0,0};
    for ( int i=0;i<1<<16;i++ )
        memory[i] = -1;

    for ( auto e : input->data ) {
        int index = 0;
        for ( int i=0;i<numInput;i++ ) {
            index += (e.inputs[i]) * (1<<i);
        }
        memory[index] = e.outputs[0];
        count[e.outputs[0]]++;
    }

    cout << "Begin Reverse-Engineer" << endl;
    cout << "\t 0: " << count[0] << endl;
    cout << "\t 1: " << count[1] << endl;

    count[0] = count[1] = 0;
    for ( int i=0;i<1<<16;i++ )
        count[ memory[i] ] ++;

    cout << "Redundancy Check" << endl;
    cout << "\t 0: " << count[0] << endl;
    cout << "\t 1: " << count[1] << endl;

    cout << "\n Tring Subset Parity" << endl;
    int df[numInput][2];
    for ( int i=0;i<numInput;i++ )
        df[i][0] = df[i][1] = 0;
    for ( int entry=0;entry<size;entry++ ) {
        int index = 0;
        for ( int i=0;i<numInput;i++ ) {
            index += (input->data[entry].inputs[i]) * (1<<i);
        }
        // try to reverse some bits
        for ( int i=0;i<numInput;i++ ) {
            if (memory[index] == memory[index ^ (1<<i)])
                df[i][0]++;
            if (memory[index] == 1-memory[index ^ (1<<i)])
                df[i][1]++;
        }
    }
    for ( int i=0;i<numInput;i++ ) {
        cout << i << " = " << df[i][0] << " : " << df[i][1] << endl;
    }
    // output->WriteFile();

    delete input;
    delete output;

}