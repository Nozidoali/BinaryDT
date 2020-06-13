#include "BinaryDT.h"

int max_index;
double entropy;

void Ind_Init() {
    max_index = 0;
}

int Ind_Get() {
    max_index ++;
    return max_index;
}

int Ind_Val() {
    return max_index;
}

int Nod_Index ( Node * node, bool imp = false ) {
    return imp? (node->literal << 1) + 2 : (node->literal << 1) + 3;
}

int Implement ( int index ) {
    return index ^ 1;
}


/**
 * Nod_WriteAag
 * node = ( literal * left ) + ( !literal * right )
 *      = !( !( literal * left ) * !( !literal * right ) )
 */
int Nod_WriteAag ( Node * node, ostream & fout ) {

    auto Build = [] ( ostream & fout, int l, int r, bool impl, bool impr, bool impo = false ) {
        int p = Ind_Get();
        int ileft  = impl? l : l^1;
        int iright = impl? r : r^1;
        fout << 2*p << " ";
        fout << ileft << " ";
        fout << iright << endl;
        return impo? 2*p+1 : 2*p;
    };

    // return if node is const
    if ( node->logic == CONST0 ) {
        return 0;
    }
    if ( node->logic == CONST1 ) {
        return 1;
    }

    // valid PI
    assert( node->literal >= 0 );

    int left  = Nod_WriteAag( node->left,  fout );
    int right = Nod_WriteAag( node->right, fout );

    int ileft, iright;
    ileft = left >= 2 ? Build( fout, Nod_Index( node ), left, 0, 0 ) : Nod_Index( node );
    iright = right >= 2 ? Build( fout, Nod_Index( node ), right, 1, 0 ) : Nod_Index( node, 1 );

    // if tree is skewed
    if ( left == 0 ) {
        return Implement( iright );
    }
    if ( right == 0 ) {
        return Implement( ileft );
    }

    // if tree is balance
    return Build( fout, ileft, iright, 1, 1, 1 );

}

void Tre_WriteAag ( Tree * tree, ostream & fout ) {
    Ind_Init();
    Nod_WriteAag( tree->root, fout );
    return;
}

/**
 * Nod_Split: return the score if spliting the index.
 */
double Nod_Split ( Node * node, Data * data, int index ) {
    double left[2], right[2];
    left[0] = left[1] = 0;
    right[0] = right[1] = 0;

    for ( auto & entry : node->entries ) {
        // index = True: left
        if ( Dat_LookUp( data, entry, index ) ) {
            left[data->output[entry]] += 1;
        }
        // index = False: right
        else {
            right[data->output[entry]] += 1;
        }
    }

    double count[2] = { left[0]+right[0], left[1]+right[1] };
    return Entropy(count) - Entropy(left) - Entropy(right);
}

/**
 * Node_Split: 
 */
void Nod_TrainDT ( Node * node, Data * data ) {
    assert( node != nullptr );
    cerr << "    Node #: " << Ind_Val();
    cerr << " Entropy: ";
    cerr.precision(2); cerr << entropy << "\r"; cerr.flush();
    double bestScore = 0;
    int bestIndex = -1;

    // try each split
    ForEachIndex( data ) {
        double score = Nod_Split( node, data, i );
        if ( score > bestScore ) {
            bestScore = score;
            bestIndex = i;
        }
    }

    // Terminate if the entropy has reached the minimum
    if ( bestIndex == -1 ) {
        node->literal = bestIndex;
        node->logic = (node->count[1] > node->count[0]? CONST1 : CONST0);
        return;
    }
    
    Ind_Get();

    entropy -= bestScore;

    // Split left node and right node
    node->literal = bestIndex;
    node->logic = MUX;

    node->left = new Node;
    node->right = new Node;
    
    for ( auto & entry : node->entries ) {
        // index = True: left
        if ( Dat_LookUp( data, entry, bestIndex ) ) {
            node->left->entries.insert( entry );
            node->left->count[data->output[entry]] += 1;
        }
        // index = False: right
        else {
            node->right->entries.insert( entry );
            node->right->count[data->output[entry]] += 1;
        }
    }

    // release the information in node
    node->entries.clear();
    
    // recursion
    Nod_TrainDT( node->left,  data );
    Nod_TrainDT( node->right, data );

}

void Tre_TrainDT ( Tree * tree, Data * data ) {

    // assign id
    Ind_Init();
    ForEachIndex( data ) {
        Ind_Get();
    }

    tree->root = new Node;
    for ( int i = 0; i < data->size; i ++ ) {
        tree->root->entries.insert( i );
        tree->root->count[data->output[i]] ++;
    }

    // initial entropy
    entropy = Entropy(tree->root->count);

    // recursion training
    Nod_TrainDT( tree->root, data ); 
    tree->size = Ind_Val();

    cerr << endl;
}