#include <iostream>
using namespace std;

#include "Hamming.h"

int main(){

    Hamming code = Hamming(2, 4);

    for(int i = 0; i < code.verification_matrix.rows; i++){
        for(int j = 0; j < code.verification_matrix.columns; j++)
        {
            cout << code.verification_matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    for(int i = 0; i < code.generating_matrix.rows; i++){
        for(int j = 0; j < code.generating_matrix.columns; j++)
        {
            cout << code.generating_matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    return 0;
}
