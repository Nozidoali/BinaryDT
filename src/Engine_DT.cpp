#include "Engine.h"

int Train ( PLA_Format * input, AIG_Format * output, unordered_set<int> & row, unordered_set<int> & col ) {

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
    auto Build = [] ( AIG_Format * formater, int l, int r, bool impl, bool impr, bool impo = false ) {
        int p = formater->input.size() + formater->output.size() + formater->nodes.size() + 1;
        int ileft  = impl? l^1 : l;
        int iright = impr? r^1 : r;
        formater->Add( ileft, iright, 2*p );
        return impo? 2*p+1 : 2*p;
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
        int count[2] = {0,0};
        for ( auto i : row ) {
            count[input->data[i].outputs[0]] ++;
        }
        return count[1] > count[0] ? 1:0;
    }

    unordered_set<int> rowLeft, rowRight, colLeft, colRight;
    for ( auto i : col ) {
        colLeft.insert( i );
        colRight.insert( i );
    }
    for ( auto i : row ) {
        if ( input->data[i].inputs[BestIndex] )
            rowLeft.insert( i );
        else
            rowRight.insert( i );
    }
    col.clear();
    row.clear();
    int left = Train( input, output, rowLeft, colLeft );
    int right = Train( input, output, rowRight, colRight );

    // degenerate
    if ( left == 0 && right == 0 ) {
        return 0;
    }

    int ileft, iright;
    ileft = left >= 2 ? Build( output, 2*BestIndex+2, left, 0, 0, 0 ) : 2*BestIndex+2;
    iright = right >= 2 ? Build( output, 2*BestIndex+3, right, 0, 0, 0 ) : 2*BestIndex+3;

    // if tree is skewed
    if ( left == 0 ) {
        return iright;
    }
    if ( right == 0 ) {
        return ileft;
    }

    // if tree is balance
    return Build( output, ileft, iright, 1, 1, 1 );
}

void DT_Manager :: ExecuteCommand () {

    // take pla as input and aag as output
    PLA_Format * input  = new PLA_Format;
    AIG_Format * output = new AIG_Format;
    input->filename = InputFileName;
    output->filename = OutputFileName;

    input->ReadFile();

    unordered_set<int> col, row;

    for (int j=0;j<input->data[0].inputs.size();j++)
        col.insert(j);
    for (int k=0;k<input->data.size();k++)
        row.insert(k);

    // define inputs
    for ( int i = 0; i< input->data[0].inputs.size(); i ++ ) {
        output->input.push_back( 2*i + 2 );
    }
    // define output and train the nodes
    output->output.push_back( Train(input, output, row, col) );  

    output->WriteFile();

    delete input;
    delete output;

}