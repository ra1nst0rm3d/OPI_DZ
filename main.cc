#include <cstdlib>
#include <iostream>
#include <algorithm>

#define SIDE 9 // сторона квадратной матрицы

#define LOW_THRESHOLD -15
#define HIGH_THRESHOLD 30

using namespace std;

void PrintMenu() {
        cout << "\nМеню: \n";
        cout << "1. Произведение элементов, следующих за максимальными в столбце по модулю.\n";
        cout << "2. Заменить отриц. элементы их квадратами и отсортировать элементы каждой строки по возрастанию.\n";
        cout << "3. Вывести максимальный элемент правого треугольника матрицы.\n";
        cout << "4. Сгенерировать матрицу и вывести её на экран.\n";
        cout << "5. Выход.\n";
}



// Устанавливает случайные значения элементов в пределах [-15; 30]
void GenerateMatrix(int (&matrix) [SIDE][SIDE]) {

        for(int i = 0; i < SIDE; i++) { 
                for(int j = 0; j < SIDE; j++) {
                        matrix[i][j] = (rand() % (HIGH_THRESHOLD + abs(LOW_THRESHOLD) + 1)) + LOW_THRESHOLD;
                }
        }

}

// Выводит матрицу на экран
void PrintMatrix(int (&matrix) [SIDE][SIDE]) {

        for(int i = 0; i < SIDE; i++) {
                for(int j = 0; j < SIDE; j++) {
                        cout << matrix[i][j] << "\t";
                }
                cout << "\n";
        }

}


// Возвращает максимальный элемент "правого треугольника" квадратной матрицы
int MaxValue(int (&matrix) [SIDE][SIDE]) {
        int tmp = LOW_THRESHOLD - 1; // -16 потому что у нас диапазон заполнения [-15, 30]

        for(int j = SIDE-1; j > (SIDE-1)/2; j--) {
                for(int i = SIDE-j; i < SIDE-1; i++) {
                        if(i > j) break;
                        if(matrix[i][j] > tmp) tmp = matrix[i][j];
                }
        }
	
        return (tmp == LOW_THRESHOLD - 1) ? 0 : tmp;
}

// Возвращает произведение элементов, следующих за максимальными в каждом столбце
int Task3(int (&matrix)[SIDE][SIDE]) {//
        int result = 1, currMax{}, maxI{}, maxJ{};

	for (int j = 0; j < SIDE; j++) {
		for (int i = 0; i < SIDE; i++) {
			if (abs(matrix[i][j]) > currMax) {
				currMax = matrix[i][j];
				maxI = i;
			}
		}
		if (maxI < SIDE && maxJ < SIDE) {
			result *= matrix[maxI + 1][maxJ];
			currMax = 0;
			maxI = 0;
			maxJ = 0;
		}
		else {
			result *= currMax;
			currMax = 0;
			maxI = 0;
			maxJ = 0;
		}
	}

	return result;

}


// Заменяет отрицательные элементы их квадратами и сортирует элементы каждой строки по возрастанию
void ReplaceNegative (int(&matrix)[SIDE][SIDE]) {
    for (int i = 0; i < SIDE; i++) {
		for (int j = 0; j < SIDE; j++) {
			if (Matrix[i][j] < 0) {
				Matrix[i][j] *= Matrix[i][j];
			}
		}
	}
}

// Сортировка строк матрицы по возрастанию
void SortMatrixByAscending(int (&matrix) [SIDE][SIDE]){
    int tmp{};

	for (int i = 0; i < SIDE; i++) {
		for (int j = 0; j < SIDE; j++) {
			for (int k = 0; k < SIDE - 1; k++) {
				if (Matrix[i][k] > Matrix[i][j]) {
					tmp = Matrix[i][k];
					Matrix[i][k] = Matrix[i][j];
					Matrix[i][j] = tmp;
				}
			}
		}
	}
}

// Функция, отрабатывающая команды пользователя
void UserHandle(int (&matrix) [SIDE][SIDE]) {
        char key{};

        PrintMenu();
        cout << "Что бы вы хотели выбрать: ";
        cin >> key;

        switch(key) {
                case '1':
                        cout << "Произведение равно " << Task3(matrix) << endl;
                        break;
                case '2':
                        ReplaceNegative(matrix);
                        SortMatrixByAscending(matrix);
                        cout << "Отсортированная матрица: \n";
                        PrintMatrix(matrix);
                        break;
                case '3':
                        cout << "Максимальный элемент равен " << MaxValue(matrix) << endl;
                        break;
                case '4':
                        GenerateMatrix(matrix);
                        cout << "Сгенерированная матрица: \n";
                        PrintMatrix(matrix);
                        break;
                case '5':
                        exit(EXIT_SUCCESS);
                default:
                        cout << "Неверный запрос!" << endl;
                        return;
        }

        return;
}

int main(int argc, char* argv[]) {
    srand(time(NULL));

    int matrix[SIDE][SIDE];

        while(true) {
                UserHandle(matrix);
        }

    return 0;
}
