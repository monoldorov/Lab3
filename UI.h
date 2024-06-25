#include<iostream>
#include"matrix.h"
#include"ArraySequence.h"
#include"tests.h"

using namespace std;

enum class State {
    MENU,
    TYPE,
    FIRST_ED,
    SECOND_ED,
    TESTS,
    EXIT
};

template<class T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& obj)
{
    for (size_t i = 0; i < obj.getSize(); ++i) {
        for (size_t j = 0; j < obj.getSize(); ++j) {
            os << obj[i][j] << "\t";
        }
        os << endl;
    }
    return os;
}

int typeChoiceView(size_t& n1, size_t& n2) {
    int tmp = -1;
    while (tmp > 4 || tmp < 1) {
        cout << "/-----------------------Тип матриц-----------------------\\" << endl;
        cout << "|                                                        |" << endl;
        cout << "|  1. Целочисненные                                      |" << endl;
        cout << "|  2. Вещественные                                       |" << endl;
        cout << "|  3. Выход                                              |" << endl;
        cout << "|                                                        |" << endl;
        cout << "\\--------------------------------------------------------/" << endl;
        cout << " >>> ";
        cin >> tmp;
    }
    if (tmp == 3) return 3;
    cout << " Введите размер первой и второй матрицы";
    cout << " >>> ";
    cin >> n1 >> n2;
    return tmp;
}

int mainMenuView() {
    int tmp = -1;
    while (tmp > 5 || tmp < 1) {
        cout << "/----------------------Главное Меню----------------------\\" << endl;
        cout << "|                                                        |" << endl;
        cout << "|  1. Создать матрицы                                    |" << endl;
        cout << "|  2. Редактировать 1 матрицу                            |" << endl;
        cout << "|  3. Редактировать 2 матрицу                            |" << endl;
        cout << "|  4. Запуск тестов                                      |" << endl;
        cout << "|  5. Выход                                              |" << endl;
        cout << "|                                                        |" << endl;
        cout << "\\--------------------------------------------------------/" << endl;
        cout << " >>> ";
        cin >> tmp;
    }
    return tmp;
}

int matrixEditView() {
    int tmp = -1;
    while (tmp > 11 || tmp < 1) {
        cout << "/----------------------Первая матрица--------------------\\" << endl;
        cout << "|                                                        |" << endl;
        cout << "|  1. Заполнить числами из консоли                       |" << endl;
        cout << "|  2. Заполнить случайными числами                       |" << endl;
        cout << "|  3. Поменять местами две строки                        |" << endl;
        cout << "|  4. Умножить строку на число                           |" << endl;
        cout << "|  5. Добавь к строке другую, умноженную на коэффициент  |" << endl;
        cout << "|  6. Умножить матрицу на число                          |" << endl;
        cout << "|  7. Вычесть вторую матрицу с коэффициентом             |" << endl;
        cout << "|  8. Умножить на вторую матрицу                         |" << endl;
        cout << "|  9. Транспонировать                                    |" << endl;
        cout << "|  10. Вывести матрицу                                   |" << endl;
        cout << "|  11. Выход                                             |" << endl;
        cout << "|                                                        |" << endl;
        cout << "\\--------------------------------------------------------/" << endl;
        cout << " >>> ";
        cin >> tmp;
    }
    return tmp;
}

void mainLoop(State state) {
    int type;
    Matrix<int> *mat1int;
    Matrix<double> *mat1double;
    Matrix<int> *mat2int;
    Matrix<double> *mat2double;
    while(1) {
        if (state == State::MENU) {
            int userCh = mainMenuView();
            if (userCh == 1) state = State::TYPE;
            if (userCh == 2) state = State::FIRST_ED;
            if (userCh == 3) state = State::SECOND_ED;
            if (userCh == 4) state = State::TESTS;
            if (userCh == 5) state = State::EXIT;
        } else
        if (state == State::TYPE) {
            size_t n1, n2;
            type = typeChoiceView(n1, n2);
            switch (type)
            {
            case 1:
                mat1int = new Matrix<int>(n1);
                mat2int = new Matrix<int>(n2);
                break;
            case 2:
                mat1double = new Matrix<double>(n1);
                mat2double = new Matrix<double>(n2);
                break;
            case 3:
                state = State::MENU;
                break;
            }
            state = State::MENU;
        } else
        if (state == State::FIRST_ED) {
            while(state == State::FIRST_ED) {
            int userCh = matrixEditView();
            if (type == 1) {
                switch (userCh) {
                    case 1:
                        for (size_t i = 0; i < mat1int->getSize(); ++i) {
                            for (size_t j = 0; j < mat1int->getSize(); ++j) {
                                cout << " >>> Элемент матрицы (" << i << ", " << j << "): ";
                                int tmp; cin >> tmp;
                                mat1int->Set(i, j, tmp);
                            }
                        }
                        break;
                    case 2:
                        for (size_t i = 0; i < mat1int->getSize(); ++i) {
                            for (size_t j = 0; j < mat1int->getSize(); ++j) {
                                mat1int->Set(i, j, rand() % 1000);
                            }
                        }
                        break;
                    case 3:
                        int ind1, ind2;
                        cout << " >>> Индекс 1-ой строки: ";
                        cin >> ind1;
                        cout << " >>> Индекс 2-ой строки: ";
                        cin >> ind2;
                        mat1int->SwapLines(ind1, ind2);
                        break;
                    case 4:
                        int ind;
                        cout << " >>> Индекс строки: ";
                        cin >> ind;
                        int k;
                        cout << " >>> Коэффициент: ";
                        cin >> k;
                        mat1int->LineMultiply(ind, k);
                        break;
                    case 5:
                        int ind11, ind21;
                        cout << " >>> Индекс 1-ой строки: ";
                        cin >> ind11;
                        cout << " >>> Индекс 2-ой строки: ";
                        cin >> ind21;
                        int k1;
                        cout << " >>> Коэффициент: ";
                        cin >> k1;
                        mat1int->AddLineToLine(ind11, ind21, k1);
                        break;
                    case 6:
                        int k2;
                        cout << " >>> Коэффициент: ";
                        cin >> k2;
                        mat1int->Multiply(k2);
                        break;
                    case 7:
                        int k3;
                        cout << " >>> Коэффициент: ";
                        cin >> k3;
                        mat1int = new Matrix<int>(*mat1int - (*mat2int * k3));
                        break;
                    case 8:
                        mat1int->Multiply(*mat2int);
                        break;
                    case 9:
                        mat1int->Transponition();
                        break;
                    case 10:
                        cout << *mat1int;
                        break;
                    case 11:
                        state = State::MENU;
                        break;
                }
                cout << *mat1int;
            }
            else {
                switch (userCh) {
                    case 1:
                        for (size_t i = 0; i < mat1double->getSize(); ++i) {
                            for (size_t j = 0; j < mat1double->getSize(); ++j) {
                                cout << " >>> Элемент матрицы (" << i << ", " << j << "): ";
                                double tmp; cin >> tmp;
                                mat1double->Set(i, j, tmp);
                            }
                        }
                        break;
                    case 2:
                        for (size_t i = 0; i < mat1double->getSize(); ++i) {
                            for (size_t j = 0; j < mat1double->getSize(); ++j) {
                                mat1double->Set(i, j, rand() % 1000);
                            }
                        }
                        break;
                    case 3:
                        int ind1, ind2;
                        cout << " >>> Индекс 1-ой строки: ";
                        cin >> ind1;
                        cout << " >>> Индекс 2-ой строки: ";
                        cin >> ind2;
                        mat1double->SwapLines(ind1, ind2);
                        break;
                    case 4:
                        int ind;
                        cout << " >>> Индекс строки: ";
                        cin >> ind;
                        double k;
                        cout << " >>> Коэффициент: ";
                        cin >> k;
                        mat1double->LineMultiply(ind, k);
                        break;
                    case 5:
                        int ind11, ind21;
                        cout << " >>> Индекс 1-ой строки: ";
                        cin >> ind11;
                        cout << " >>> Индекс 2-ой строки: ";
                        cin >> ind21;
                        double k1;
                        cout << " >>> Коэффициент: ";
                        cin >> k1;
                        mat1double->AddLineToLine(ind11, ind21, k1);
                        break;
                    case 6:
                        double k2;
                        cout << " >>> Коэффициент: ";
                        cin >> k2;
                        mat1double->Multiply(k2);
                        break;
                    case 7:
                        double k3;
                        cout << " >>> Коэффициент: ";
                        cin >> k3;
                        mat1double = new Matrix<double>(*mat1double - (*mat2double * k3));
                        break;
                    case 8:
                        mat1double->Multiply(*mat2double);
                        break;
                    case 9:
                        mat1double->Transponition();
                        break;
                    case 10:
                        cout << *mat1double;
                        break;
                    case 11:
                        state = State::MENU;
                        break;
                }
                cout << *mat1double;
            }
        }
        } else
        if (state == State::SECOND_ED) {
            while(state == State::SECOND_ED) {
            int userCh = matrixEditView();
            if (type == 1) {
                switch (userCh) {
                    case 1:
                        for (size_t i = 0; i < mat2int->getSize(); ++i) {
                            for (size_t j = 0; j < mat2int->getSize(); ++j) {
                                cout << " >>> Элемент матрицы (" << i << ", " << j << "): ";
                                int tmp; cin >> tmp;
                                mat2int->Set(i, j, tmp);
                            }
                        }
                        break;
                    case 2:
                        for (size_t i = 0; i < mat2int->getSize(); ++i) {
                            for (size_t j = 0; j < mat2int->getSize(); ++j) {
                                mat2int->Set(i, j, rand() % 1000);
                            }
                        }
                        break;
                    case 3:
                        int ind1, ind2;
                        cout << " >>> Индекс 1-ой строки: ";
                        cin >> ind1;
                        cout << " >>> Индекс 2-ой строки: ";
                        cin >> ind2;
                        mat2int->SwapLines(ind1, ind2);
                        break;
                    case 4:
                        int ind;
                        cout << " >>> Индекс строки: ";
                        cin >> ind;
                        int k;
                        cout << " >>> Коэффициент: ";
                        cin >> k;
                        mat2int->LineMultiply(ind, k);
                        break;
                    case 5:
                        int ind11, ind21;
                        cout << " >>> Индекс 1-ой строки: ";
                        cin >> ind11;
                        cout << " >>> Индекс 2-ой строки: ";
                        cin >> ind21;
                        int k1;
                        cout << " >>> Коэффициент: ";
                        cin >> k1;
                        mat2int->AddLineToLine(ind11, ind21, k1);
                        break;
                    case 6:
                        int k2;
                        cout << " >>> Коэффициент: ";
                        cin >> k2;
                        mat2int->Multiply(k2);
                        break;
                    case 7:
                        int k3;
                        cout << " >>> Коэффициент: ";
                        cin >> k3;
                        mat2int = new Matrix<int>(*mat2int - (*mat2int * k3));
                        break;
                    case 8:
                        mat2int->Multiply(*mat2int);
                        break;
                    case 9:
                        mat2int->Transponition();
                        break;
                    case 10:
                        cout << *mat2int;
                        break;
                    case 11:
                        state = State::MENU;
                        break;
                }
                cout << *mat2int;
            }
            else {
                switch (userCh) {
                    case 1:
                        for (size_t i = 0; i < mat2double->getSize(); ++i) {
                            for (size_t j = 0; j < mat2double->getSize(); ++j) {
                                cout << " >>> Элемент матрицы (" << i << ", " << j << "): ";
                                double tmp; cin >> tmp;
                                mat2double->Set(i, j, tmp);
                            }
                        }
                        break;
                    case 2:
                        for (size_t i = 0; i < mat2double->getSize(); ++i) {
                            for (size_t j = 0; j < mat2double->getSize(); ++j) {
                                mat2double->Set(i, j, rand() % 1000);
                            }
                        }
                        break;
                    case 3:
                        int ind1, ind2;
                        cout << " >>> Индекс 1-ой строки: ";
                        cin >> ind1;
                        cout << " >>> Индекс 2-ой строки: ";
                        cin >> ind2;
                        mat2double->SwapLines(ind1, ind2);
                        break;
                    case 4:
                        int ind;
                        cout << " >>> Индекс строки: ";
                        cin >> ind;
                        double k;
                        cout << " >>> Коэффициент: ";
                        cin >> k;
                        mat2double->LineMultiply(ind, k);
                        break;
                    case 5:
                        int ind11, ind21;
                        cout << " >>> Индекс 1-ой строки: ";
                        cin >> ind11;
                        cout << " >>> Индекс 2-ой строки: ";
                        cin >> ind21;
                        double k1;
                        cout << " >>> Коэффициент: ";
                        cin >> k1;
                        mat2double->AddLineToLine(ind11, ind21, k1);
                        break;
                    case 6:
                        double k2;
                        cout << " >>> Коэффициент: ";
                        cin >> k2;
                        mat2double->Multiply(k);
                        break;
                    case 7:
                        double k3;
                        cout << " >>> Коэффициент: ";
                        cin >> k3;
                        mat2double = new Matrix<double>(*mat2double - (*mat2double * k));
                        break;
                    case 8:
                        mat2double->Multiply(*mat2double);
                        break;
                    case 9:
                        mat2double->Transponition();
                        break;
                    case 10:
                        cout << *mat2double;
                        break;
                    case 11:
                        state = State::MENU;
                        break;
                }
                cout << *mat2double;
            }
            }
        } else
        if (state == State::TESTS) {
            runAllTests();
            state = State::MENU;
        } else
        if (state == State::EXIT) {
            exit(0);
            break;
        }
    }
}
