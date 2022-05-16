#include <iostream>
using namespace std;

#include "Hamming.h"

int main(){

    Hamming code = Hamming(3, 4);

    for(int i = 0; i < code.ver_matrix.rows; i++){
        for(int j = 0; j < code.ver_matrix.columns; j++)
        {
            cout << code.ver_matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    for(int i = 0; i < code.gen_matrix.rows; i++){
        for(int j = 0; j < code.gen_matrix.columns; j++)
        {
            cout << code.gen_matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    return 0;
}
