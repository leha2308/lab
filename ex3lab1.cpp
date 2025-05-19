#include "ex3lab1.h"

complex::complex(double r, double i) : real(r), imag(i){}

complex complex::operator+=(const complex& other)
{
    real += other.real;
    imag += other.imag;
    return *this;
}

complex complex::operator+(const complex& other) const
{
    complex result = *this;
    result += other;
    return result;
}

complex complex::operator-=(const complex& other)
{
    real -= other.real;
    imag -= other.imag;
    return *this;
}

complex complex::operator-(const complex& other) const
{
    complex result = *this;
    result -= other;
    return result;
}

complex complex::operator*=(const complex& other)
{
    double r = real * other.real - imag * other.imag;
    double i = real * other.imag + imag * other.real;
    real = r;
    imag = i;
    return *this;
}

complex complex::operator*(const complex& other) const
{
    complex result = *this;
    result *= other;
    return result;
}

complex& complex::operator/=(const complex& other) {
    double denom = other.real * other.real + other.imag * other.imag;
    if (denom == 0.0) {
        throw std::invalid_argument("Division by zero");
    }
    double r = (real * other.real + imag * other.imag) / denom;
    double i = (imag * other.real - real * other.imag) / denom;
    real = r;
    imag = i;
    return *this;
}

complex complex::operator/(const complex& other) const {
    complex result = *this;
    result /= other;
    return result;
}


double complex::module() const
{
    return real * real + imag * imag;
}

double complex::argument()
{
    return std::atan2(imag, real);
}

  std::ostream& operator<<(std::ostream& os, const complex& z) {
    os << z.real << (z.imag >= 0 ? " + " : " - ") << std::abs(z.imag) << "i";
    return os;
}

  std::istream& operator>>(std::istream& is, complex& z) {
    // Ожидается ввод двух чисел: real imag
    is >> z.real >> z.imag;
    return is;
}

int main()
{

    complex a(3, 4);     // 3 + 4i
    complex b(1, -2);    // 1 - 2i

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;

    std::cout << "a + b = " << (a + b) << std::endl;
    std::cout << "a - b = " << (a - b) << std::endl;
    std::cout << "a * b = " << (a * b) << std::endl;
    std::cout << "a / b = " << (a / b) << std::endl;

    complex c = a;
    c += b;
    std::cout << "c += b: " << c << std::endl;

    complex d = a;
    d *= b;
    std::cout << "d *= b: " << d << std::endl;

    complex e = a;
    e /= b;
    std::cout << "e /= b: " << e << std::endl;

    std::cout << "Module a: " << a.module() << std::endl;
    std::cout << "Argument a (in radians): " << a.argument() << std::endl;

    // Проверка ввода
    complex input_z;
    std::cout << "Enter a complex number (real imag): ";
    std::cin >> input_z;
    std::cout << "Вы ввели: " << input_z << std::endl;

    return 0;

}