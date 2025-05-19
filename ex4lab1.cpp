#include "ex4lab1.h"
#include <iostream>


    matrix::matrix(size_t r, size_t c)
            : rows(r), cols(c), data(nullptr)
    {
        //std::cout << "DEBUG: rows = " << rows << ", cols = " << cols << '\n';

        if (rows == 0 || cols == 0)
        {
            throw std::invalid_argument("Invalid values");
        }

        //std::cout << rows << " " << cols;

        if (rows > 10000 || cols > 10000) {
            throw std::length_error("Matrix dimensions too large");
        }

        data = new double*[rows];
        for (std::size_t i = 0; i < rows; ++i)
        {
            data[i] = new double[cols]{};
        }
        if (!*data)
        {
            throw std::bad_alloc ();
        }

        for(size_t i = 0; i < rows; ++i)
        {
            for(size_t j; j < cols; ++j)
            {
                data[i][j] = 0.0;
            }
        }

    }

   matrix::matrix(const matrix& other)
            : rows(other.rows), cols(other.cols)
    {
        data = new double*[rows];
        for (std::size_t i = 0; i < rows; ++i) {
            data[i] = new double[cols];
            for (std::size_t j = 0; j < cols; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
    }


    matrix matrix::operator+(const matrix& other) const
    {

        if (this->rows != other.rows || this->cols != other.cols)
        {
            throw std::invalid_argument("Invalid size of matrix");
        }

        matrix result (this->rows, this->cols);


        for (std::size_t i = 0; i < rows; ++i) {
            for (std::size_t j = 0; j < cols; ++j) {
                result.data[i][j] = this->data[i][j] + other.data[i][j];
            }
        }

        return result;

    }

    matrix matrix::operator-(const matrix& other) const
    {

        if (this->rows != other.rows || this->cols != other.cols)
        {
            throw std::invalid_argument("Invalid size of matrix");
        }

        matrix result (this->rows, this->cols);


        for (std::size_t i = 0; i < rows; ++i) {
            for (std::size_t j = 0; j < cols; ++j) {
                result.data[i][j] = this->data[i][j] - other.data[i][j];
            }
        }

        return result;

    }



    matrix matrix::operator*(const matrix& other) const
    {

        if (this->cols != other.rows)
        {
            throw std::invalid_argument("Invalid size of matrix");
        }

        matrix result (this->rows, this->cols);


        for (std::size_t i = 0; i < this->rows; ++i) {
            for (std::size_t j = 0; j < other.cols; ++j) {
                result.data[i][j] = 0.0;
                for (std::size_t k = 0; k < this->cols; ++k) {
                    result.data[i][j] += this->data[i][k] * other.data[k][j];
                }
            }
        }

        return result;

    }

    matrix matrix::operator*(double scalar) const
    {

        matrix result(this->rows, this->cols);

        for(size_t i = 0; i < this->rows; ++i)
        {

            for(size_t j = 0; j < this->cols; ++j)
            {

                result.data[i][j] = this->data[i][j] * scalar;

            }

        }
        return  result;
    }

    matrix matrix::transpose() const
    {

        matrix result(this->rows, this->cols);

        for(size_t i = 0; i < rows; ++i)
        {
            for(size_t j = 0; j < cols; ++j)
            {
                result.data[j][i] = this->data[i][j];
            }

        }

        return result;

    }

    double matrix::determinant() const
    {
        if (rows != cols)
        {
            throw std::invalid_argument("Matrix must be square");
        }

        std::size_t n = rows;
        double** temp = new double*[n];
        for (size_t i = 0; i < n; ++i)
        {
            temp[i] = new double[n];
            for (size_t j = 0; j < n; ++j)
            {
                temp[i][j] = data[i][j];
            }
        }

        double det = 1.0;
        int sign = 1;

        for (size_t i = 0; i < n; ++i)
        {
            // Поиск главного элемента в столбце
            std::size_t pivot = i;
            for (size_t j = i + 1; j < n; ++j)
            {
                if (std::abs(temp[j][i]) > std::abs(temp[pivot][i]))
                {
                    pivot = j;
                }
            }

            // Если элемент на диагонали — 0, определитель равен 0
            if (std::abs(temp[pivot][i]) < 1e-9)
            {
                det = 0.0;
                break;
            }

            // Перестановка строк
            if (i != pivot)
            {
                std::swap(temp[i], temp[pivot]);
                sign *= -1;
            }

            det *= temp[i][i];

            // Обнуление элементов ниже диагонали
            for (size_t j = i + 1; j < n; ++j)
            {
                double factor = temp[j][i] / temp[i][i];
                for (size_t k = i; k < n; ++k)
                {
                    temp[j][k] -= factor * temp[i][k];
                }
            }
        }

        for (size_t i = 0; i < n; ++i)
        {
            delete[] temp[i];
        }
        delete[] temp;

        return det * sign;
    }

    matrix matrix::inverse() const
    {
        if (rows != cols)
        {
            throw std::invalid_argument("Matrix must be square to invert");
        }

        size_t n = rows;
        matrix result(n, n);
        matrix temp(*this);


        for (size_t i = 0; i < n; ++i)
        {
            result.data[i][i] = 1.0;
        }

        for (size_t i = 0; i < n; ++i)
        {

            size_t pivot = i;
            for (size_t j = i + 1; j < n; ++j)
            {
                if (std::abs(temp.data[j][i]) > std::abs(temp.data[pivot][i])) {
                    pivot = j;
                }
            }

            if (std::abs(temp.data[pivot][i]) < 1e-9)
            {
                throw std::runtime_error("Matrix is singular and cannot be inverted");
            }


            if (i != pivot)
            {
                std::swap(temp.data[i], temp.data[pivot]);
                std::swap(result.data[i], result.data[pivot]);
            }


            double diag = temp.data[i][i];
            for (size_t j = 0; j < n; ++j)
            {
                temp.data[i][j] /= diag;
                result.data[i][j] /= diag;
            }


            for (size_t j = 0; j < n; ++j)
            {
                if (j == i) continue;
                double factor = temp.data[j][i];
                for (size_t k = 0; k < n; ++k)
                {
                    temp.data[j][k] -= factor * temp.data[i][k];
                    result.data[j][k] -= factor * result.data[i][k];
                }
            }
        }

        return result;
    }

    matrix::~matrix()
    {
        delete data;
        data = nullptr;
    }

    double* matrix:: operator[](std::size_t i)
    {
    if (i >= rows)
    {
        throw std::out_of_range("Row index out of range");
    }
    return data[i]; // возвращаем указатель на строку
}

   const double* matrix::operator[](std::size_t i) const
   {
    if (i >= rows)
    {
        throw std::out_of_range("Row index out of range");
    }
    return data[i]; // возвращаем указатель на строку (для const-объектов)
}

// Метод для вывода матрицы
   void matrix::print() const
   {
    for (std::size_t i = 0; i < rows; ++i)
    {
        for (std::size_t j = 0; j < cols; ++j)
        {
            std::cout << data[i][j] << " ";
        }
        std::cout << '\n';
    }
}


matrix operator*(double scalar, matrix& m)
{
    return m * scalar;
}


int main()
{

    try {
        // Создание матрицы 2x2
        matrix m1(2, 2);
        matrix A(2, 3);
        matrix B(3, 2);

        // Заполнение A
        A[0][0] = 1; A[0][1] = 2; A[0][2] = 3;
        A[1][0] = 4; A[1][1] = 5; A[1][2] = 6;

        // Заполнение B
        B[0][0] = 7;  B[0][1] = 8;
        B[1][0] = 9;  B[1][1] = 10;
        B[2][0] = 11; B[2][1] = 12;

        // Заполнение матрицы
        m1[0][0] = 4;
        m1[0][1] = 7;
        m1[1][0] = 2;
        m1[1][1] = 6;


        std::cout << "Matrix:\n";
        m1.print();

        double det = m1.determinant();
        std::cout << "Determinant: " << det << '\n';

        

        matrix C = A * B;

        std::cout << "A * B = \n";
        C.print();

        std::cout << "Original matrix:\n";
        m1.print();




        matrix sum = m1 + m1;

        std::cout << "\nSum of matrix with itself:\n";
        sum.print();

        matrix scaled = 2.0 * m1;

        std::cout << "\nMatrix multiplied by 2:\n";
        scaled.print();



    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }

    return 0;

}