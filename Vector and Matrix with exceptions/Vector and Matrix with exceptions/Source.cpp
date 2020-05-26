#include <iostream>
#include <stdio.h>
#include <cassert>
using namespace std;
class Except
{
private:
    int error;
    string txt[3] = { "Index out of range", "Wrong matrix sizes", "Divide by zero" };
public:
    static const int indexOutOfRangeException = 0;
    static const int wrongSizes = 1;
    static const int divideByZero = 2;
    Except(int _error) : error(_error) {};
    string text() { return txt[error]; };
    friend ostream& operator<<(ostream& stream, const Except ex);
};
ostream& operator<<(ostream& stream, Except ex)
{
    return stream << ex.text() << endl;;
}
class Vector
{
    int x;
    int y;
    int z;
public:
    //Конструктор по умолчанию
    Vector() : x(0), y(0), z(0)
    {}
    //Конструктор с параметрами
    Vector(int _x, int _y, int _z) :
        x(_x), y(_y), z(_z)
    {
        cout<<"just writing from Vector";
    }
    //Конструктор копирования
    Vector(const Vector& vector) :
        x(vector.x),
        y(vector.y),
        z(vector.z)
    {
        cout << "copy writing from Vector";
    }
    int getx();
    int gety();
    int getz();
    //Оператор сложения
    friend Vector operator+(Vector const& a, Vector const& b)
    {
        int g = a.x + b.x;
        int h = a.y + b.y;
        int j = a.z + b.z;
        Vector c(g, h, j);
        return c;
    }
    //Оператор вычитания
    Vector operator- (const Vector& oth)
    {
        Vector tmp;
        tmp.x = x - oth.x;
        tmp.y = y - oth.y;
        tmp.z = z - oth.z;
        return tmp;
    }
    //Оператор магического умножения
    friend Vector operator*(Vector const& a, Vector const& b)
    {
        Vector tmp;
        tmp.x = a.x * b.x;
        tmp.y = a.y * b.y;
        tmp.z = a.z * b.z;
        cout << "its a magic ☼" << endl;
        return tmp;
    }
    //Оператор присваивания
    Vector& operator= (const Vector& oth)
    {
        if (this != &oth)
        {
            cout << "Operator= V " << this << endl;
            x = oth.x;
            y = oth.y;
            z = oth.z;
        }
        return *this;
    }
    //Оператор индексации
    int& operator[](int index)
    {
        if (index == 0)
            return x;
        else if (index == 1)
            return y;
        else if (index == 2)
            return z;
        else throw Except(Except::indexOutOfRangeException);
    }
};
//Вывод координат
int Vector::getx() { return x; }
int Vector::gety() { return y; }
int Vector::getz() { return z; }
class Matrix
{
    int** a;
    int column;
    int row;
public:
    //Конструктор по умолчанию
    Matrix() : a(nullptr), column(0), row(0) {}
    //Конструктор с параметрами
    Matrix(int _column, int _row) :
        column(_column), row(_row)
    {
        if (_column < 1 || _row < 1)
            throw Except(Except::indexOutOfRangeException);
        a = new int* [row];
        for (int count = 0; count < row; count++)
        {
            a[count] = new int[column];
        }
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                a[i][j] = 3; /*rand() % 10;*/
            }
        }
        cout << "just writing from Matrix\n";
    }
    //Конструктор копирования
    Matrix(const Matrix& matrix) : column(matrix.column), row(matrix.row)
    {
        a = new int* [row];
        for (int i = 0; i < row; i++)
        {
            a[i] = new int[column];
        }
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
                a[i][j] = matrix.a[i][j];
        }

        cout << "copy writing from Matrix\n";
    }
    //Вывод матрицы
    void getm();
    //Оператор сложения
    Matrix operator+(const Matrix& oth)
    {
        Matrix tmp(oth.column, row);

        if (row == oth.row && column == oth.column)
        {
            for (int i = 0; i < row; i++)
                for (int j = 0; j < column; j++)
                {
                    tmp.a[i][j] = a[i][j] + oth.a[i][j];
                }
        }

        else throw Except(Except::wrongSizes);

        return tmp;
    }
    //Опертор вычитания
    Matrix operator-(const Matrix& oth)
    {
        Matrix tmp(oth.column, row);

        if (row == oth.row && column == oth.column)
        {
            for (int i = 0; i < row; i++)
                for (int j = 0; j < column; j++)
                {
                    tmp.a[i][j] = a[i][j] - oth.a[i][j];
                }
        }
        else throw Except(Except::wrongSizes);
        return tmp;
    }
    //Оператор присваивания
    Matrix& operator=(const Matrix& oth)
    {
        cout << "Operator= from Matrix " << this << endl;
        if (this != &oth)
        {
            if (a != nullptr)
            {
                for (int count = 0; count < row;

                    count++)
                    delete[] this->a[count];
            }
            column = oth.column;
            row = oth.row;
            a = new int* [this->row];
            for (int count = 0; count < this->row; count++)
            {
                a[count] = new int[this->column];
            }

            for (int i = 0; i < row; i++)
                for (int j = 0; j < column; j++)
                {
                    a[i][j] = oth.a[i][j];
                }
        }
        return *this;
    }
    //Оператор умножения
    Matrix operator*(Matrix const& oth)
    {
        //int* arr = new int [c.row*c.column];
        //for (int k = 0; k < c.row * c.column;k++)
        // arr[k] = 0;
        //int p1 = 0;
        //int p2 = 0;
        //int p3 = 0;
        //for (int i = 0; i < c.column; i++)
        //{
        // for (int j = 0; j < c.row; j++)
        // {
        // arr[i]+=(c.a[j+p1])*(b.a[p3+p2]);//МУСОР??
        // p2 += c.row;
        // }
        // if (p3 == c.row)
        // {
        // p3 = 0;
        // }
        // else p3 = i+1;
        // p1+=c.column;
        // p2 = 0;
        // }
        //Matrix p12(arr);
        //delete[] arr;
        //return p12;
        if (row == oth.column)
        {
            Matrix tmp(row, oth.column);
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < oth.column; j++)
                {
                    int lol = 0;
                    for (int k = 0; k < column; k++)
                    {
                        lol += a[i][k] * a[k][j];
                    }
                    tmp.a[i][j] = lol;
                }
            }
            return tmp;
        }
        else throw Except(Except::wrongSizes);
    }
    //Деструктор
    ~Matrix()
    {
        if (a != nullptr)///////////////////////////////////////////////
        {
            for (int i = 0; i < row; i++)
            {
                delete[] a[i];
            }
            delete[] a;
        }
    }
};
//Вывод матрицы подробнее
void Matrix::getm()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            cout << a[i][j] << "\t";
        }
        cout << "\n";
    }
}
int main()
{
    Vector q(3, 4, 1);
    cout << " " << q.getx() << " " << q.gety() << " " << q.getz() << endl;
    Vector w(6, 2, 1);
    cout << " " << w.getx() << " " << w.gety() << " " << w.getz() << endl;
    Vector e = q;
    cout << " " << e.getx() << " " << e.gety() << " " << e.getz() << endl;
    Vector m = q + w;
    cout << " " << m.getx() << " " << m.gety() << " " << m.getz() << endl;
    Vector n = q * w;
    cout << " " << n.getx() << " " << n.gety() << " " << n.getz() << endl;
    try
    {
        q[3] = 2;
        cout << "variable change" << " ";
        cout << " " << q.getx() << " " << q.gety() << " " << q.getz() << endl;
    }
    catch (Except& Exception)
    {
        cout << Exception << endl;
    }
    Matrix r(2, 2);
    r.getm();
    Matrix t(2, 2);
    t.getm();
    try
    {
        Matrix u = r * t;
        u.getm();
    }
    catch (Except& Exception)
    {
        cout << Exception << endl;
    }
    try
    {
        Matrix y = r + t;
        y.getm();
    }
    catch (Except& Exception)
    {
        cout << Exception << endl;
    }
    return 0;
}