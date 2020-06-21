#include "Engine.h"

void Run( string input, string output, string command ) {
    manager = new Manager( input, output, command );
    if ( command == "DT" ) {
        ((DT_Manager *)manager)->ExecuteCommand();
    }
    else if ( command == "RT" ) { 
        ((RT_Manager *)manager)->ExecuteCommand();
    }
    else if ( command == "NT" ) { 
        ((NT_Manager *)manager)->ExecuteCommand();
    }
    else if ( command == "RD" ) { 
        ((RD_Manager *)manager)->ExecuteCommand();
    }
};
