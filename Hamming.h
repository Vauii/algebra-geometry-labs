//
// Created by Евгений on 16.05.2022.
//

#ifndef MATRIX_CLASS_HAMMING_H
#define MATRIX_CLASS_HAMMING_H
#include "Matrix.h"

class Hamming{

public:

    Matrix<int> ver_matrix;
    Matrix<int> gen_matrix;


    Hamming(int p, int r): ver_matrix(r, (pow(p, r) - 1) / (p - 1), 0),
                           gen_matrix(((pow(p, r) - 1) / (p - 1)) - r,(pow(p, r) - 1) / (p - 1), 0){

        for (int i = 0; i < r; i++){

            ver_matrix[i][ver_matrix.columns - r + i] = 1;

        }

        int * temp_column = new int[r], current_index = ver_matrix.columns - r;
        for (int i = 0; i < r; i++) temp_column[i] = 0;

        while(next(temp_column, p, r)){

            if (column_checkout(temp_column, current_index, p)){

                bool null = true;
                for (int j = 0; j < r; j++) {

                    if (temp_column[j] != 0){

                        null = false;

                    }
                }

                if (!null){

                    for (int k = 0; k < r; k++){

                        ver_matrix[k][current_index-1] = temp_column[k];

                    }
                    current_index--;

                }

            }

        }



        for (int i = 0; i < gen_matrix.rows; i++){

            gen_matrix[i][i] = 1;

        }
        for (int i = 0; i < gen_matrix.rows; i++){
            for (int j = gen_matrix.rows; j < gen_matrix.columns; j++){

                gen_matrix[i][j] = (p - ver_matrix[j - gen_matrix.rows][i]) % p;

            }
        }


    }

    ~Hamming(){

        cout << 1 << endl;
        delete &ver_matrix;
        delete &gen_matrix;
        cout << 2;

    }


    static bool next(int *a, int p, int size)
    {

        int i = 0;
        a[0]++;

        while(a[i] == p){

            if (i == size - 1) return false;
            a[i] = 0;
            a[i+1]++;
            i++;

        }

        return true;

    }

    bool column_checkout(const int * temp, int index, int p) const{

        int *prev = new int[ver_matrix.columns], right_border = ver_matrix.columns, col_len = ver_matrix.rows;

        for (int i = index; i < right_border; i++){

            for (int k = 0; k < col_len; k++){

                prev[k] = ver_matrix[k][i];

            }

            for (int num = 1; num < p; num++){

                bool same = true;
                for (int l = 0; l < col_len; l++) {
                    if ((temp[l] * num) % p != prev[l]){

                        same = false;
                        break;

                    }
                }
                if (same) return false;

            }

        }
        return true;

    }


    static int pow(int x, int y){

        int temp = 1;
        for (int i = 0; i < y; i++) temp *= x;
        return temp;

    }

};


#endif //MATRIX_CLASS_HAMMING_H
