#include "complexnumber.h"

ComplexNumber::ComplexNumber() : real(0.0), imaginary(0.0)
{

}

ComplexNumber::ComplexNumber(double r, double i)
{
    this->real = r;
    this->imaginary = i;
}

ComplexNumber::ComplexNumber(ComplexNumber const& o)
{
    this->real = o.real;
    this->imaginary = o.imaginary;
}

double ComplexNumber::getReal()
{
    return real;
}

void ComplexNumber::setReal(double real)
{
    this->real = real;
}

double ComplexNumber::getImaginary()
{
    return imaginary;
}

void ComplexNumber::setImaginary(double im)
{
    this->imaginary = im;
}

ComplexNumber ComplexNumber::add(ComplexNumber rh)
{
    return ComplexNumber(this->real + rh.real, this->imaginary + rh.imaginary);
}

ComplexNumber ComplexNumber::mul(ComplexNumber rh)
{
    return ComplexNumber(this->real*rh.real - this->imaginary*rh.imaginary, this->imaginary*rh.real + this->real*rh.imaginary);
}

ComplexNumber ComplexNumber::operator+(ComplexNumber rh)
{
    return add(rh);
}

ComplexNumber ComplexNumber::operator*(ComplexNumber rh)
{
    return mul(rh);
}

double ComplexNumber::value()
{
    return sqrt(real*real + imaginary*imaginary);
}
