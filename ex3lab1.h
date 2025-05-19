#ifndef INC_2ЛАБАИРБЫ_EX3LAB1_H
#define INC_2ЛАБАИРБЫ_EX3LAB1_H

#include <iostream>
#include <cmath>

class complex
{

private:

    double real = 0; // действительная часть
    double imag = 0; // мнимая

public:

    double getReal() const { return real; }
    double getImag() const { return imag; }

    complex (double r = 0.0, double i = 0.0);


    complex operator+=(const complex& other);



    complex operator+(const complex& other) const;



    complex operator-=(const complex& other);


    complex operator-(const complex& other) const;


    complex operator*=(const complex& other);


    complex operator*(const complex& other) const;

    complex& operator/=(const complex& other) ;

    complex operator/(const complex& other) const ;


    double module() const;
    double argument();
    friend  std::ostream& operator<<(std::ostream& os, const complex& z) ;
    friend std::istream& operator>>(std::istream& is, complex& z) ;

};





#endif //INC_2ЛАБАИРБЫ_EX3LAB1_H
