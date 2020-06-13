#include "BinaryDT.h"

double Entropy ( double count[] ) {
    // calculate entropy (0+1)! / 0!1!
    double sum = count[0] + count[1];
    double entropy = sum * log( sum + 1 );
    entropy -= count[0] * log( count[0] + 1 );
    entropy -= count[1] * log( count[1] + 1 );
    return entropy;
}

void Dat_LoadPla ( Data * data, istream & fin ) {
    int count = 0;
    string input, output;
    while ( true ) {
        fin >> input;
        // return if reaching the EOF
        if ( input == ".e" ) {
            cerr << endl;
            return;
        }
        // get input number
        else if ( input == ".i" ) {
            fin >> data->numInput;
            cerr << "    Input: " << data->numInput; fflush( stderr );
        }
        // get output number
        else if ( input == ".o" ) {
            fin >> data->numOutput; // should be 1
            cerr << " Ouput: " << data->numOutput; fflush( stderr );
        }
        // get size and allocate memory
        else if ( input == ".p" ) {
            fin >> data->size;
            data->input  = new bool [ data->size * data->numInput  ];
            data->output = new bool [ data->size * data->numOutput ];
            cerr << " Size: " << data->size; fflush( stderr );
        }
        // get type
        else if ( input == ".type" ) {
            fin >> output;
        }
        // get data
        else {
            bool * offset = data->input + count * data->numInput;
            // get input
            ForEachIndex( data ) {
                *(offset+i) = input[i] == '1';
            }
            // get output
            fin >> output;
            data->output[count++] = output == "1";
        }
    }
}

void Dat_Free ( Data * data ) {
    delete data->input;  data->input  = nullptr;
    delete data->output; data->output = nullptr;
    delete data; data = nullptr;
} 

bool Dat_LookUp ( Data * data, int entry, int index ) {
    return data->input[ entry * data->numInput + index ];
}