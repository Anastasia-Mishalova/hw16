// hw16.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <algorithm>

using namespace std;

//Создайте шаблонный класс матрица. Необходимо реализовать динамическое выделение памяти, очистку памяти, заполнение матрицы с клавиатуры, 
//заполнение случайными значениями, отображение матрицы, арифметические операции с помощью перегруженных операторов(+, –, *, / ),
//поиск макс и мин значений матрицы

template <typename T>
class Matrix
{
private:
    T** M;
    int m;
    int n;

public:

    Matrix()
    {
        n = m = 0;
    }

    Matrix(int m, int n)
    {
        this->m = m;
        this->n = n;

        M = (T**) new T * [m];

        for (int i = 0; i < m; i++)
            M[i] = (T*)new T[n];

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                M[i][j] = 0;
    }

    Matrix(const Matrix& _M)
    {
        m = _M.m;
        n = _M.n;

        M = (T**) new T * [m];

        for (int i = 0; i < m; i++)
            M[i] = (T*) new T[n];

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                M[i][j] = _M.M[i][j];
    }

    void randomValues()
    {
        for (int i = 0; i < m; i++)
        {

            for (int j = 0; j < n; j++)
            {
                M[i][j] = rand() % 201 - 100;
            }
        }
    }

    void inputValues()
    {
        for (int i = 0; i < m; i++)
        {

            for (int j = 0; j < n; j++)
            {
                cout << "Введите число: ";
                cin >> M[i][j];
            }
        }
    }

    void Print()
    {
        cout << endl;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
                cout << M[i][j] << " ";
            cout << endl;
        }
        cout << endl << endl;
    }

    int& operator()(int m, int n)
    {
        return M[m][n];
    }

    Matrix operator+(Matrix& other)
    {
        if (m != other.m || n != other.n)
        {
            throw invalid_argument("Матрицы разного размера");
        }

        Matrix result(m, n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                result(i, j) = M[i][j] + other(i, j);
            }
        }

        return result;
    }

    Matrix operator-(Matrix& other)
    {
        if (m != other.m || n != other.n)
        {
            throw invalid_argument("Матрицы разного размера");
        }

        Matrix result(m, n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                result(i, j) = M[i][j] - other(i, j);
            }
        }

        return result;
    }

    Matrix operator*(Matrix& other)
    {
        if (m != other.m || n != other.n)
        {
            throw invalid_argument("Матрицы разного размера");
        }

        Matrix result(m, n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                result(i, j) = M[i][j] * other(i, j);
            }
        }

        return result;
    }

    Matrix operator/(Matrix& other)
    {
        if (m != other.m || n != other.n)
        {
            throw invalid_argument("Матрицы разного размера");
        }

        Matrix result(m, n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                result(i, j) = M[i][j] / other(i, j);
            }
        }

        return result;
    }

    Matrix operator=(const Matrix& _M)
    {
        if (n > 0)
        {
            for (int i = 0; i < m; i++)
                delete[] M[i];
        }

        if (m > 0)
        {
            delete[] M;
        }

        m = _M.m;
        n = _M.n;

        M = (T**) new T * [m];
        for (int i = 0; i < m; i++)
        {
            M[i] = (T*) new T[n];
        }


        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                M[i][j] = _M.M[i][j];
            }
        }

        return *this;
    }

    void minimum()
    {
        int min = M[0][0];
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (M[i][j] < min)
                {
                    min = M[i][j];
                }
            }
        }
        cout << "Минимальное число: " << min;
        cout << endl;
    }

    void maximum()
    {
        int max = M[0][0];
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (M[i][j] > max)
                {
                    max = M[i][j];
                }
            }
        }
        cout << "Максимальное число: " << max;
        cout << endl;
    }

    ~Matrix()
    {
        if (n > 0)
        {
            for (int i = 0; i < m; i++)
                delete[] M[i];
        }

        if (m > 0)
            delete[] M;
    }


};

void main()
{
    setlocale(LC_ALL, "ru");

    Matrix<int> M1(3, 3);

    //M1.randomValues();
    M1.inputValues();
    M1.Print();
    M1.minimum();
    M1.maximum();

    cout << "\nКопирование";
    Matrix<int> M2;
    M2 = M1;
    M2.Print();

    cout << "Оператор сложения";
    Matrix<int> M3;
    M3 = M1 + M2;
    M3.Print();

    cout << "Оператор вычитания";
    Matrix<int> M4;
    M4 = M1 - M2;
    M4.Print();

    cout << "Оператор умножения";
    Matrix<int> M5;
    M5 = M1 * M2;
    M5.Print();

    cout << "Оператор деления";
    Matrix<int> M6;
    M6 = M1 / M2;
    M6.Print();

}