#include "Format.h"

void PLA_Format :: ReadFile() {
    ifstream fin ( filename );
    int temp_int;
    string temp_str;
    string input, output;
    while ( true ) {
        fin >> input;
        // return if reaching the EOF
        if ( input == ".e" ) {
            return;
        }
        // get input number
        else if ( input == ".i" ) {
            fin >> temp_str;
        }
        // get output number
        else if ( input == ".o" ) {
            fin >> temp_str;
        }
        // get size and allocate memory
        else if ( input == ".p" ) {
            fin >> temp_str;
        }
        // get type
        else if ( input == ".type" ) {
            fin >> temp_str;
        }
        // get data
        else {
            
            Entry entry;
            entry.inputs.clear();
            entry.outputs.clear();
            // get input
            for ( auto ch : input ) {
                entry.inputs.push_back(ch=='1');
            }
            // get output
            fin >> output;
            for ( auto ch : output ) {
                entry.outputs.push_back(ch=='1');
            }
            data.push_back( entry );   
        }
    }
    
    fin.close();
}
