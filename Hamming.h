//
// Created by Евгений on 16.05.2022.
//

#ifndef MATRIX_CLASS_HAMMING_H
#define MATRIX_CLASS_HAMMING_H
#include "Matrix.h"

class Hamming{

public:

    Matrix<int> verification_matrix;
    Matrix<int> generating_matrix;
    int p;


    Hamming(int input_p, int r): verification_matrix(r, (pow(input_p, r) - 1) / (input_p - 1), 0),
                                 generating_matrix(((pow(input_p, r) - 1) / (input_p - 1)) - r, (pow(input_p, r) - 1) / (input_p - 1), 0){

        p = input_p;

        for (int i = 0; i < r; i++){

            verification_matrix[i][verification_matrix.columns - r + i] = 1;

        }

        int * temp_column = new int[r], current_index = verification_matrix.columns - r;
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

                        verification_matrix[k][current_index - 1] = temp_column[k];

                    }
                    current_index--;

                }

            }

        }



        for (int i = 0; i < generating_matrix.rows; i++){

            generating_matrix[i][i] = 1;

        }
        for (int i = 0; i < generating_matrix.rows; i++){
            for (int j = generating_matrix.rows; j < generating_matrix.columns; j++){

                generating_matrix[i][j] = (p - verification_matrix[j - generating_matrix.rows][i]) % p;

            }
        }


    }

    ~Hamming(){

        delete &verification_matrix;
        delete &generating_matrix;

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

        int *prev = new int[verification_matrix.columns], right_border = verification_matrix.columns, col_len = verification_matrix.rows;

        for (int i = index; i < right_border; i++){

            for (int k = 0; k < col_len; k++){

                prev[k] = verification_matrix[k][i];

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


    Matrix<int> decode(Matrix<int> x){

        int r = verification_matrix.rows, n = verification_matrix.columns;
        int *vector = new int[r];

        for (int i = 0; i < r; i++){
            for (int j = 0; j < n; j++){

                vector[i] = x[0][j] * verification_matrix[i][j];

            }
        }

        bool no_mistakes = true;
        for (int j = 0; j < n; j++){
            if (vector[j] != 0){

                no_mistakes = false;
                break;

            }
        }

        if (!no_mistakes){

            int mistake_index = -1, correct_alpha;
            for (int i = 0; i < n; i++){
                for (int alpha = 1; alpha < p; alpha++){

                    bool equal = true;
                    for (int k = 0; k < r; k++){
                        if (vector[k] != alpha * verification_matrix[k][i]){

                            equal = false;
                            break;

                        }
                    }

                    if (equal){

                        mistake_index = i;
                        correct_alpha = alpha;
                        break;

                    }

                }

                if (mistake_index != -1) break;

            }

            x[0][mistake_index] = x[0][mistake_index] - correct_alpha;

        }

        Matrix<int> u = Matrix<int>(1, generating_matrix.rows);
        for (int j = 0; j < generating_matrix.rows; j++) {
            u[0][j] = x[0][j];
        }

        return u;

    }



};


#endif //MATRIX_CLASS_HAMMING_H
