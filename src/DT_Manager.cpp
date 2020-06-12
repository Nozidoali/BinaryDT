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

void Man_Free ( Manager * man ) {
    Dat_Free ( man->data );
    delete man; man = nullptr;
}