#ifndef INC_2ЛАБАИРБЫ_EX4LAB1_H
#define INC_2ЛАБАИРБЫ_EX4LAB1_H

#include <iostream>
#include <cmath>
#include <utility>


class matrix
{

private:
    double **data;
    size_t rows = 0;
    size_t cols = 0;

public:

    matrix(size_t r, size_t c);


    matrix(const matrix& other);



    matrix operator+(const matrix& other) const;


    matrix operator-(const matrix& other) const;




    matrix operator*(const matrix& other) const;


    matrix operator*(double scalar) const;


    matrix transpose() const;


    double determinant() const;

    matrix inverse() const;

    double *operator[](size_t i);

    const double* operator[](std::size_t i) const;

    void print() const;

    ~matrix();

};

matrix operator*(double scalar, matrix& m);

#endif //INC_2ЛАБАИРБЫ_EX4LAB1_H
