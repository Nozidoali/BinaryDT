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


    // output->WriteFile();

    delete input;
    delete output;

}