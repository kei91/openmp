/*
Клеточное поле
Дата   матрица   M,   заполненная   случайными   числами.   Клетки   матрицы   раскрашены   как 
шахматная доска. Необходимо рассчитать суммы чисел в белых клетках и черных клетках. 
Полученные суммы сравнить, и вывести наибольшую.
*/
#include <iostream>
#include <omp.h>
#include <stdlib.h>
#include <time.h>  

using namespace std;

#define M 3

int main() {
	srand (time(NULL));
	int ** chess = new int*[M];
	for (int i = 0; i < M; ++i) { chess[i] = new int[M]; }
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < M; ++j) {
			chess[i][j] = rand() % 9;
		 	cout << chess[i][j] << " ";
		}
		cout << endl;
	}
	int black = 0, white = 0;
	#pragma omp parallel
	{
		#pragma omp for reduction(+: black) reduction(+: white)
			for (int i = 0; i < M; ++i) 
				for (int j = 0; j < M; ++j) 
				{
					if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))
						black += chess[i][j];
					if ((i % 2 == 0 && j % 2 != 0) || (i % 2 != 0 && j % 2 == 0))
						white += chess[i][j];
				}	
	}
	cout << "white: " << white << " black: " << black << endl;
	if(white > black) cout << "white bigger: " << white << endl;
	else if (white < black) cout << "black bigger: " << black << endl;
	else cout << "equal " << black << endl;
	return 0;
}
