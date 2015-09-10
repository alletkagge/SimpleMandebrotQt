#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <QImage>
#include <QVector2D>

#include "complexnumber.h"

ComplexNumber mandelbrot(ComplexNumber z, ComplexNumber c);

void drawMandelbrot(QImage & image, int iterations, QVector2D offset, double size, ComplexNumber critical = ComplexNumber(0, 0));

#endif // MANDELBROT_H

