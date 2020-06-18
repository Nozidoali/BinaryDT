#include "Engine.h"

bool Train ( PLA_Format * input, vector<int> & row, vector<int> & col ) {
    if (col.size() == 0) {
        return true;
    }
    auto Split = [&] ( int index ) {
        auto Entropy = [ ] ( double * count ) {
            double sum = count[0] + count[1];
            double entropy = sum * log( sum + 0.0001 );
            entropy -= count[0] * log( count[0] + 0.0001 );
            entropy -= count[1] * log( count[1] + 0.0001 );
            return entropy;
        };
        double left[2], right[2];
        left[0] = left[1] = 0;
        right[0] = right[1] = 0;
        for ( auto i : row ) {
            PLA_Format::Entry entry = input->data[i];
            if ( entry.inputs[index] )
                left[entry.outputs[0]] += 1;
            else
                right[entry.outputs[0]] += 1;
        }
        double count[2] = { left[0]+right[0], left[1]+right[1] };
        return Entropy(count) - Entropy(left) - Entropy(right);
    };
    int BestIndex = -1;
    double BestScore = 0;
    for ( auto i : col ) {
        double score = Split(i);
        if( BestScore < score ) {
            BestScore = score;
            BestIndex = i;
        }
    }
    
    if ( BestIndex==-1 ) {
        int count[2];
        count[0] = count[1] = 0;
        for ( auto i : row ) {
            count[input->data[i].outputs[0]] ++;
        }
        return min(count[0], count[1]) == 0;
    }

    vector<int> rowLeft, rowRight, colLeft, colRight;
    for ( auto i : col ) {
        colLeft.push_back( i );
        colRight.push_back( i );
    }
    for ( auto i : row ) {
        if ( input->data[i].inputs[BestIndex] )
            rowLeft.push_back( i );
        else
            rowRight.push_back( i );
    }
    col.clear();
    row.clear();
    int lError = Train( input, rowLeft, colLeft );
    if (!lError)
        return false;
    int rError = Train( input, rowRight, colRight );
    if (!rError)
        return false;

    return true;

}

void DT_Manager :: ExecuteCommand () {

    // take pla as input and aag as output
    PLA_Format * input  = new PLA_Format;
    AIG_Format * output = new AIG_Format;
    input->filename = InputFileName;
    output->filename = OutputFileName;

    input->ReadFile();

    vector<int> col, row;

    for (int i=0;i<16;i++) {
        for (int j=0;j<16 && j!=i;j++)
            col.push_back(j);
        for (int k=0;k<6400;k++)
            row.push_back(k);
        cout << i << " : " << Train(input, row, col) << endl;  
        col.clear();
        row.clear();          
    }



    // output->WriteFile();

    delete input;
    delete output;

}