#include "Engine.h"

void Run( string input, string output, string command ) {
    manager = new Manager( input, output, command );
    if ( command == "DT" ) {
        ((DT_Manager *)manager)->ExecuteCommand();
    }
    else {

    }
};
