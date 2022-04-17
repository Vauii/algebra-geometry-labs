#include <iostream>
using namespace std;

template<typename T> class Matrix{
public:
// Public Additional Inherited Members

    int rows = 0;
    int columns = 0;
    T ** values = nullptr;


// Public Member Functions

    Matrix(int rs, int cols): rows(rs), columns(cols){

        values = new T * [rows];
        for (int i = 0; i < rows; i++)
            values[i] = new T [columns];

    }


    Matrix(int rs, int cols, const T &value): rows(rs), columns(cols){

        values = new T * [rows];

        for (int i = 0; i < rows; i++)
            values[i] = new T [columns];

        for (int i = 0; i < rows; i++){
            for (int j = 0; j < columns; j++){

                values[i][j] = value;

            }
        }

    }


    Matrix(const Matrix &matrix){

        rows = matrix.rows;
        columns = matrix.columns;
        values = new T * [rows];

        for (int i = 0; i < rows; i++)
            values[i] = new T [columns];

        for (int i = 0; i < rows; i++){
            for (int j = 0; j < columns; j++){

                values[i][j] = matrix[i][j];

            }
        }

    }


    ~Matrix(){

        for (int i = 0; i < rows; i++)
            delete[] values[i];
        delete[] values;

    }


    T & operator() (int row, int col){

        return values[row][col];

    }


    const T & operator() (int row, int col) const{

        return values[row][col];

    }


    Matrix & operator= (const Matrix &matrix){

        if (this == &matrix) {
            return *this;
        }

        rows = matrix.rows;
        columns = matrix.columns;
        values = new T * [rows];

        for (int i = 0; i < rows; i++)
            values[i] = new T [columns];

        for (int i = 0; i < rows; i++){
            for (int j = 0; j < columns; j++){

                values[i][j] = matrix[i][j];

            }
        }

        return *this;

    }


    Matrix & operator= (const T &value){

        for (int i = 0; i < rows; i++){
            for (int j = 0; j < columns; j++){

                values[i][j] = value;

            }
        }

        return *this;

    }


    T * operator[] (int row){

        return values[row];

    }


    const T * operator[] (int row) const{

        return values[row];

    }


    friend Matrix operator+ (const Matrix &a, const Matrix &b){

        if ((a.rows != b.rows) || (a.columns != b.columns)){

            cout << "MATH ERROR: the shape of the matrices must be identical";
            exit(-1);

        }

        Matrix res = Matrix(a.rows, a.columns);
        for(int i = 0; i < res.rows; i++){
            for(int j = 0; j < res.columns; j++){

                res[i][j] = a[i][j] + b[i][j];

            }
        }

        return res;

    }


    friend Matrix operator+ (const Matrix &a, const T &value){

        Matrix res = Matrix(a.rows, a.columns);
        for(int i = 0; i < res.rows; i++){
            for(int j = 0; j < res.columns; j++){

                res[i][j] = a[i][j] + value;

            }
        }

        return res;

    }


    friend Matrix operator+ (const T &value, const Matrix &a){

        Matrix res = Matrix(a.rows, a.columns);
        for(int i = 0; i < res.rows; i++){
            for(int j = 0; j < res.columns; j++){

                res[i][j] = a[i][j] + value;

            }
        }

        return res;

    }


    friend Matrix operator- (const Matrix &a, const Matrix &b){

        if ((a.rows != b.rows) || (a.columns != b.columns)){

            cout << "MATH ERROR: the shape of the matrices must be identical";
            exit(-1);

        }

        Matrix res = Matrix(a.rows, a.columns);
        for(int i = 0; i < res.rows; i++){
            for(int j = 0; j < res.columns; j++){

                res[i][j] = a[i][j] - b[i][j];

            }
        }

        return res;

    }


    friend Matrix operator- (const Matrix &a, const T &value){

        Matrix res = Matrix(a.rows, a.columns);
        for(int i = 0; i < res.rows; i++){
            for(int j = 0; j < res.columns; j++){

                res[i][j] = a[i][j] - value;

            }
        }

        return res;

    }


    friend Matrix operator- (const T &value, const Matrix &a){

        Matrix res = Matrix(a.rows, a.columns);
        for(int i = 0; i < res.rows; i++){
            for(int j = 0; j < res.columns; j++){

                res[i][j] = value - a[i][j];

            }
        }

        return res;

    }


    friend Matrix operator* (const Matrix &a, const Matrix &b){

        if (a.columns != b.rows){

            cout << "MATH ERROR: matrix multiplication requires equality of left matrix number of columns"
                    " and right matrix number of rows";
            exit(-1);

        }

        Matrix res = Matrix(a.rows, b.columns);
        for(int i = 0; i < res.rows; i++){
            for(int j = 0; j < res.columns; j++){

                res[i][j] = 0;
                for(int k = 0; k < a.columns; k++){

                    res[i][j] += a[i][k] * b[k][j];

                }
            }
        }

        return res;

    }


    friend Matrix operator* (const Matrix &a, const T &value){

        Matrix res = Matrix(a.rows, a.columns);
        for(int i = 0; i < res.rows; i++){
            for(int j = 0; j < res.columns; j++){

                res[i][j] = a[i][j] * value;

            }
        }

        return res;

    }


    friend Matrix operator* (const T &value, const Matrix &a){

        Matrix res = Matrix(a.rows, a.columns);
        for(int i = 0; i < res.rows; i++){
            for(int j = 0; j < res.columns; j++){

                res[i][j] = a[i][j] * value;

            }
        }

        return res;

    }


    friend bool operator== (const Matrix &a, const Matrix &b){

        if ((a.rows != b.rows) || (a.columns != b.columns)){

            return false;

        }

        for(int i = 0; i < a.rows; i++){
            for(int j = 0; j < a.columns; j++){

                if (a[i][j] != b[i][j])
                    return false;

            }
        }

        return true;

    }


    friend bool operator== (const Matrix &a, const T &value){

        for(int i = 0; i < a.rows; i++){
            for(int j = 0; j < a.columns; j++){

                if (a[i][j] != value)
                    return false;

            }
        }

        return true;

    }


    friend bool operator== (const T &value, const Matrix &a){

        for(int i = 0; i < a.rows; i++){
            for(int j = 0; j < a.columns; j++){

                if (a[i][j] != value)
                    return false;

            }
        }

        return true;

    }


    Matrix transpose(){

        Matrix transposed_matrix = Matrix(columns, rows);
        for (int i = 0; i < columns; i++){
            for (int j = 0; j < rows; j++){

                transposed_matrix[i][j] = values[j][i];

            }
        }

        return transposed_matrix;

    }


    void swap_elements(double &a, double &b){

        double additional_variable = a;
        a = b;
        b = additional_variable;

    }


    void swap_rows(double top_row[], double bottom_row[], int &l, int &n){

        for(int i = l; i < n; i++){

            swap_elements(top_row[i], bottom_row[i]);

        }

    }


    void add_multiplied_row(const double added_row[], double variable_row[], double coefficient, int l, int n){

        for(int i = l; i < n; i++){

            variable_row[i] += added_row[i] * coefficient;

        }

    }


    double calc_det(){

        if (rows != columns){

            cout << "MATH ERROR: it is possible to calculate the determinant only for square matrices";
            exit(-1);

        }

        double determinant = 1, coefficient, leading_element;
        double matrix[rows][columns];

        for (int i = 0; i < columns; i++){
            for (int j = 0; j < columns; j++){

                matrix[i][j] = values[i][j];

            }
        }

        for (int j = 0; j < columns; j++){

            for (int i = j; i < columns; i++){

                if (matrix[i][j] != 0){

                    if (i != j){

                        swap_rows(matrix[j], matrix[i], j, columns);
                        determinant *= -1;

                    }
                    leading_element = matrix[j][j];


                    for (int g = j+1; g < columns; g++){

                        coefficient = -matrix[g][j]/leading_element;
                        if (coefficient != 0){

                            add_multiplied_row(matrix[j], matrix[g], coefficient, j, columns);

                        }

                    }
                    break;

                }
            }
        }

        for(int i = 0; i < columns; i++){

            determinant *= matrix[i][i];

        }

        return determinant;

    }


// Static Public Member Functions

    static Matrix eye(int rs, int cols){

        Matrix e = Matrix(rs, cols, 0);
        for(int i = 0; i < e.rows && i < e.columns; i++){

            e[i][i] = 1;

        }
        return e;

    }


    static Matrix zeros(int rs, int cols){

        Matrix z = Matrix(rs, cols, 0);
        return z;

    }

};


int main(){

    Matrix<double> a = Matrix<double>(5, 6, 1);
    Matrix<double> b = Matrix<double>(Matrix<double>::eye(10, 20));

    cout << a[2][3] << endl;
    cout << b[5][6] << endl;
    cout << (a == b) << endl;
    cout << (b * 20)[1][1] << endl;

    a[2][3] = 23.241124;
    a = a + 20;
    cout << a(2, 3) + 2 << endl;

    Matrix<double> c = Matrix<double>(a);
    cout << (a == c) << endl;

    Matrix<double> z = Matrix<double>(4, 4, 1);
    z[0][0] = 3;
    z[1][1] = 3;
    z[2][2] = 3;
    z[3][3] = 3;
    cout << z.calc_det() << endl;
}
