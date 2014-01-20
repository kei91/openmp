/*
Миноры вам не мажоры
Дана большая матрица A размером N x N. Минором M(2,3) называется определитель матрицы 
N­1 x N­1, полученной из A вычеркиванием строки 2 и столбца 3. Сгенерировать случайную 
матрицу   A.   Найти   все   её   миноры.   Вычислить   среднее   арифметическое   миноров.   Для 
распараллеливания использовать OpenMP.
*/

#include <iostream>
#include <cmath>
#include <omp.h>
#include <stdlib.h>
#include <time.h>  
#include <vector>

using namespace std;

double determ(int** arr, int size) {
    int i, j;
    double det = 0;
    int ** m;
    if(size == 1) { det = arr[0][0]; }
    else if(size == 2) { det = arr[0][0]*arr[1][1] - arr[0][1]*arr[1][0]; }
    else {
        m = new int*[size - 1];
        for(i = 0; i < size; ++i) {
            for(j = 0; j < size - 1; ++j) {
                if(j < i) { m[j] = arr[j]; } 
                else { m[j] = arr[j + 1]; }
            }
            det += pow((double)-1, (i + j))*determ(m, size - 1)*arr[i][size - 1];
        }
        delete [] m;
    }
    return det;
}

void print(int **arr, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << "------------\n";
}

int main() {
    srand(time(NULL));
    int N = 0;
    cout << "N: ";
    cin >> N;
    vector<int> minor;
    int ** matrix = new int*[N];
    int ** temp = new int*[N - 1];
    for (int i = 0; i < N; ++i) { 
        matrix[i] = new int[N];
        temp[i] = new int[N - 1]; 
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = rand() % 9;
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    int det = 0;
    #pragma omp parallel
    {
        #pragma omp for reduction(+: det)
            for(int i = 0; i < N ; ++i) {
                for (int j = 0; j < N; ++j) {
                    for (int l = 0; l < N; ++l) {
                        for (int k = 0; k < N; ++k) {
                            if (l < i && k < j) { temp[l][k] = matrix[l][k]; }
                            else if (l < i && k > j) { temp[l][k - 1] = matrix[l][k]; }
                            else if (l > i && k < j) { temp[l - 1][k] = matrix[l][k]; }
                            else if (l > i && k > j) { temp[l - 1][k - 1] = matrix[l][k]; }
                        }
                    }
                    //print(temp, N - 1);
                    //cout << "det = " << determ(temp, N - 1) << endl;
                    det += determ(temp, N - 1);
                }
            }
    }
    cout << (double)det/(N*N) << endl;

    for (int i = 0; i < N; i++) {
        delete [] matrix[i];
        delete [] temp[i];
    }
    delete [] matrix;
    delete [] temp;
    return 0;
}
