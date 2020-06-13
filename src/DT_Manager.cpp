#include "BinaryDT.h"

Manager * Man_Init () {
    return new Manager;
}

void Man_LoadFile ( Manager * man, string filename ) {
    ifstream fin ( filename );
    cerr << "Reading from: " << filename << endl;

    // initialize data
    if ( man->data == nullptr ) {
        man->data = new Data;
    }
    // load pla to data
    Dat_LoadPla( man->data, fin );
    fin.close();
}

void Man_WriteAag ( Manager * man, string filename ) {

    AIG_Format * formater = new AIG_Format;
    formater->filename = filename;
    for ( int i = 0; i< man->data->numInput; i ++ ) {
        formater->input.push_back( 2*i + 2 );
    }
    Tre_WriteAag( man->dtree, formater );
    formater->output.push_back( ( formater->input.size() + formater->nodes.size() ) * 2 + 1 );
    formater->WriteFile();

}

void Man_WriteBlif ( Manager * man, string filename ) {
    ofstream fout ( filename );
    fout << ".model" << man->name;
    
}

void Man_TrainDT ( Manager * man ) {
    cerr << "Training Decision Tree:" << endl;
    if ( man->dtree == nullptr ) {
        man->dtree = new Tree;
    }
    Tre_TrainDT( man->dtree, man->data );
}

void Man_Free ( Manager * man ) {
    Dat_Free ( man->data );
    delete man; man = nullptr;
}
