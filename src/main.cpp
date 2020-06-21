#include "Engine.h"

int main( int argc, char * argv[] ) {

    // #include "Binary DT"
    // if ( strcmp ( argv[1], "train" ) == 0 ) {
    //     Manager * man = Man_Init();
    //     Man_LoadFile( man, argv[2] );
    //     Man_TrainDT ( man );
    //     Man_WriteAag( man, argv[3] );
    //     Man_Free( man );
    // }

    if ( strcmp( argv[1], "train" ) == 0 ) {
        Run(argv[2],argv[3],"DT");
    }

    

    return 0;
}