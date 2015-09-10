#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H

#include <cmath>

class ComplexNumber
{
public:
    double real;
    double imaginary;

    ComplexNumber();
    ComplexNumber(double r, double i);
    ComplexNumber(ComplexNumber const& o);

    double getReal();
    void setReal(double real);

    double getImaginary();
    void setImaginary(double im);

    ComplexNumber add(ComplexNumber rh);

    ComplexNumber mul(ComplexNumber rh);

    ComplexNumber operator+(ComplexNumber rh);

    ComplexNumber operator*(ComplexNumber rh);

    double value();

};

#endif // COMPLEXNUMBER_H
