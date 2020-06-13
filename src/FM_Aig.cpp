#include "Format.h"

void AIG_Format :: WriteFile () {
    ofstream fout ( filename );
    fout << "aag " << input.size() + nodes.size() << " " << input.size() << " 0 " << output.size() << " " << nodes.size() << endl;
    for ( auto index : input ) {
        fout << index << endl;
    }
    for ( auto index : output ) {
        fout << index << endl;
    }
    for ( auto node : nodes ) {
        fout << node.out << " " << node.left << " " << node.right << endl;
    }
}

void AIG_Format :: Add( int _left, int _right, int _out ) {
    Node node;
    node.left = _left;
    node.right = _right;
    node.out = _out;
    nodes.push_back(node);
}