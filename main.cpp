#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;



class matrix
    {
        private:
            int k,m;
            int **mtrx;
        public:
            matrix():k(3),m(3)//матрица без параметров по умолчанию 3 на 3
             {
                 mtrx = new int *[k];
                 for(int i=0;i<k;i++)
                 {
                    mtrx[i] = new int [m];
                 }

                 for (int i = 0; i < k; i++)
                    for (int j = 0; j < m; j++)
                        mtrx[i][j] = 0;
            }

            matrix(int a, int b): k(a), m(b)//матрица с параметрами
            {
                mtrx=new int *[k];
                for(int i=0;i<k;i++)
                    {
                        mtrx[i]=new int[m];
                    }
               for (int i = 0; i < k; i++)
                    for (int j = 0; j < m; j++)
                        mtrx[i][j] = 0;
            }
            void read(char *name)//считывание матрицы с файла
            {
                ifstream Fin(name);
                Fin >> k >> m;
                for(int i=0;i<k;i++)
                {
                    for(int j=0;j<m;j++)
                    {
                        Fin >> mtrx[i][j];
                    }
                }
            }
            void printMatrix()//вывод матрицы на консоль
            {
                for (int i = 0; i < k; i++)
                {
                    for (int j = 0; j < m; j++)
                    {
                        cout << mtrx[i][j] << " ";
                    }

                    cout << endl;
                }
            }
            void set_matrix(int i, int j, int x)//установка значения матрицы
            {
                mtrx[i][j]=x;
            }
            int get_matrix(int i, int j)//получение значения матрицы
            {
                return mtrx[i][j];
            }
            void tr()//транспонирование матрицы
            {
                int **mtrx2=new int *[m];
                for(int i=0;i<m;i++)
                {
                    mtrx2[i]=new int[k];
                }

                for(int i=0;i<k;i++)
                {
                    for(int j=0;j<m;j++)
                    {
                        mtrx2[j][i]=mtrx[i][j];
                    }
                }
                swap(m,k);
                mtrx=mtrx2;
                delete[]mtrx2;
            }

            int lines()//получение количества строк матрицы
            {
                return k;
            }

            int columns()//получение количества столбцов матрицы
            {
                return m;
            }
            const matrix& operator= (matrix &mx1)//перегрузка оператора присваивания
            {
                if(&mx1==this)
                {
                    return *this;
                }
                else
                {
                    int m, k;
                m=mx1.lines();
                k=mx1.columns();
                this->m=m;
                this->k=k;
                for(int i=0;i<m;i++)
                    {
                        for(int j=0;j<k;j++)
                            {
                                this->set_matrix(i,j, mx1.get_matrix(i,j));
                            }
                    }
                return *this;
                }

    }

            ~matrix()//деструктор
            {
                for (int i = 0; i < k; i++)
                    delete [] mtrx[i];
            }

    };
    const matrix operator+(matrix &mx1, matrix &mx2)//перегрузка оператора сложения
    {
        int m1, k1, m2, k2;
        m1=mx1.lines();
        k1=mx1.columns();
        m2=mx2.lines();
        k2=mx2.columns();
        if (m1 == m2 && k1 == k2)
        {
            matrix result(m1, k1);
            for(int i=0;i<m1;i++)
            {
                for(int j=0;j<k1;j++)
                {
                    result.set_matrix(i, j, mx1.get_matrix(i, j)+mx2.get_matrix(i,j));
                }
            }
            return result;
        }
        else
        {
            throw  invalid_argument("Different size of matrix");
        }


    }
    matrix operator-(matrix &mx1, matrix &mx2)//перегрузка оператора вычитания
    {
        int m1, k1, m2, k2;
        m1=mx1.lines();
        k1=mx1.columns();
        m2=mx2.lines();
        k2=mx2.columns();
        if (m1 == m2 && k1 == k2)
        {
            matrix result(m1, k1);
            for(int i=0;i<m1;i++)
            {
                for(int j=0;j<k1;j++)
                {
                    result.set_matrix(i, j, mx1.get_matrix(i, j)-mx2.get_matrix(i,j));
                }
            }
            return result;
        }
        else
        {
            throw  invalid_argument("Different size of matrix");
        }
    }

    matrix operator*(matrix &mx1, matrix& mx2)//перегрузка оператора умножения
    {
        int m1, k1, m2, k2, numb;
        m1=mx1.lines();
        k1=mx1.columns();
        m2=mx2.lines();
        k2=mx2.columns();
        if (k1 == m2)
        {
            matrix result(m1, k2);
            for(int i=0;i<m1;i++)
            {
                for(int j=0;j<k1;j++)
                {
                    numb=0;
                    for(int k=0;k<k1;k++)
                    {
                        numb+=mx1.get_matrix(i,k)*mx2.get_matrix(k,j);
                    }
                    result.set_matrix(i, j, numb);

                }
            }
            return result;
        }
        else
        {
            throw  invalid_argument("Different size of matrix");
        }
    }

    istream& operator>> (istream& is, matrix& mx)//перегрузка оператора ввода
    {
        int m, k, number;
        k=mx.lines();
        m=mx.columns();
        for(int i=0;i<k;i++)
        {
            for(int j=0;j<m;j++)
            {
                is >> number;
                mx.set_matrix(i,j,number);
            }
        }
        return is;
    }
    ostream& operator<<(ostream& os, matrix& mx)//перегрузка оператора вывода
    {
        int m, k, number;
        k=mx.lines();
        m=mx.columns();
        for(int i=0;i<k;i++)
        {
            for(int j=0;j<m;j++)
            {
                number=mx.get_matrix(i,j);
                os << number << " ";
            }
            os << endl;
        }
        return os;
    }
    matrix operator+= (matrix &mx1, matrix& mx2)//перегрузка оператора +=
    {
        int m1, k1, m2, k2;
        m1=mx1.lines();
        k1=mx1.columns();
        m2=mx2.lines();
        k2=mx2.columns();
        if (m1 == m2 && k1 == k2)
        {
            for(int i=0;i<m1;i++)
            {
                for(int j=0;j<k1;j++)
                {
                    mx1.set_matrix(i, j, mx1.get_matrix(i, j)+mx2.get_matrix(i,j));
                }
            }
            return mx1;
        }
        else
        {
            throw  invalid_argument("Different size of matrix");
        }
    }

    matrix operator-= (matrix &mx1, matrix& mx2)//перегрузка оператора -=
    {
        int m1, k1, m2, k2;
        m1=mx1.lines();
        k1=mx1.columns();
        m2=mx2.lines();
        k2=mx2.columns();
        if (m1 == m2 && k1 == k2)
        {
            for(int i=0;i<m1;i++)
            {
                for(int j=0;j<k1;j++)
                {
                    mx1.set_matrix(i, j, mx1.get_matrix(i, j)-mx2.get_matrix(i,j));
                }
            }
            return mx1;
        }
        else
        {
            throw  invalid_argument("Different size of matrix");
        }
    }

    matrix operator*=(matrix &mx1, matrix& mx2)//перегрузка оператора *=
    {
        int m1, k1, m2, k2, numb;
        m1=mx1.lines();
        k1=mx1.columns();
        m2=mx2.lines();
        k2=mx2.columns();
        if (k1 == m2)
        {
            for(int i=0;i<m1;i++)
            {
                for(int j=0;j<k1;j++)
                {
                    numb=0;
                    for(int k=0;k<k1;k++)
                    {
                        numb+=mx1.get_matrix(i,k)*mx2.get_matrix(k,j);
                    }
                    mx1.set_matrix(i, j, numb);

                }
            }
            return mx1;
        }
        else
        {
            throw  invalid_argument("Different size of matrix");
        }
    }



int main()
{
    int line, column, digit, num1, num2;
    matrix mx1;
    matrix mx2;
    matrix mx3;
    mx1.set_matrix(0, 1, 5);
    mx2.set_matrix(2, 2, 6);
    mx3=mx1;
    cout << mx3;
    //mx1.set_matrix(0, 0, 2);
    //mx1.read("input.txt");
    //cout << mx1;
    //mx1.printMatrix();
    /*matrix mx2(3,5);
    mx2.set_matrix(2, 1, 3);
    cout << "Enter a number of columns and lines in matrix: ";
    cin >> num1 >> num2;
    matrix mx2(num1, num2);
    cout << "Enter a value of line and column that you want to change: ";
    cin >> line, column;
    cout << endl << "Enter a new value: ";
    cin >> digit;
    cout << "Enter a value of line and column that you want to return: ";
    cin >> line >> column;
    matrix mx;
    mx.read("matrix.txt");
    mx.set_matrix(line, column, digit);
    mx.get_matrix(line, column);*/
    return 0;
}
