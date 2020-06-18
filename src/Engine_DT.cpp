#include "Engine.h"

void DT_Manager :: ExecuteCommand () {

    // take pla as input and aag as output
    PLA_Format * input  = new PLA_Format;
    AIG_Format * output = new AIG_Format;
    input->filename = InputFileName;
    output->filename = OutputFileName;

    input->ReadFile();

    output->WriteFile();

    delete input;
    delete output;

}