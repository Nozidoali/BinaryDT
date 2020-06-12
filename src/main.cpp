#include "BinaryDT.h"

/**
 * Parser
 */
parser Cmdline_Parser( int argc, char * argv[] )
{
    parser option;
    option.add < string > ( "input",  'i', "Input PLA file",  true, "./benchmarks/c17.blif");
    option.add < string > ( "output", 'o', "Output BLIF file", false, "");
    option.parse_check( argc, argv );
    return option;
}

int main() {

    string iFileName, oFileName;

    auto Format = [] ( int number, Mode mode ) {
        ostringstream temp;
        temp << "Benchmarks/ex"; // replaced by input directory
        temp.width( 2 ); temp.fill('0'); temp << number;
        temp << ( mode == TRAIN ? ".train.pla" : ".valid.pla" );
        return temp.str();
    };

    for ( int i = 0; i < 100; i++ ) {
        cerr << "====== Start Training #" << i+1 << " / 100 ======" << endl;
        Manager * man = Man_Init();
        Man_LoadFile( man, Format( i, TRAIN ) );
        Man_Free( man );
    }
    
    return 0;
}