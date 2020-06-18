#include "Engine.h"

bool NTest ( PLA_Format * input, unordered_set<int> & row, unordered_set<int> & col ) {
    if (row.size() == 0) {
        return true;
    }
    if (col.size() == 0) {
        int count[2] = {0,0};
        for ( auto i : row ) {
            count[input->data[i].outputs[0]] ++;
        }
        return min(count[0], count[1]) == 0;
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

    if ( BestIndex == -1 ) {
        int count[2] = {0,0};
        for ( auto i : row ) {
            count[input->data[i].outputs[0]] ++;
        }
        return min(count[0], count[1]) == 0;
    }

    int index = BestIndex;
    unordered_set<int> rowLeft, rowRight, colLeft, colRight;
    for ( auto i : col ) {
        if (i==index) continue;
        colLeft.insert( i );
        colRight.insert( i );
    }
    for ( auto i : row ) {
        if ( input->data[i].inputs[index] )
            rowLeft.insert( i );
        else
            rowRight.insert( i );
    }
    col.clear();
    row.clear();

    return NTest( input, rowLeft, colLeft ) && NTest( input, rowRight, colRight );

}

void NT_Manager :: ExecuteCommand () {

    // take pla as input and aag as output
    PLA_Format * input  = new PLA_Format;
    AIG_Format * output = new AIG_Format;
    input->filename = InputFileName;
    output->filename = OutputFileName;

    input->ReadFile();

    unordered_set<int> col, row;

    unordered_set<int> IRE; // irredandant entries
    unordered_set<int> RE; // redandant entries
    int numInput = input->data[0].inputs.size();
    int size = input->data.size();

    for (int k=0;k<size;k++)
        row.insert(k);
    for (int k=0;k<numInput;k++)
        col.insert(k);

    if ( NTest(input, row, col) ) {
        cout << "Noise Free!" << endl;
    }

    // output->WriteFile();

    delete input;
    delete output;

}