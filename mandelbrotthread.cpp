#include <QDebug>

#include "mandelbrotthread.h"

#include "mandelbrot.h"

int MandelbrotThread::iterations;
ComplexNumber MandelbrotThread::critical;
double MandelbrotThread::zoom;
QVector2D MandelbrotThread::offset;
QImage* MandelbrotThread::image;

int MandelbrotThread::getIterations()
{
    return iterations;
}

void MandelbrotThread::setIterations(int value)
{
    iterations = value;
}

ComplexNumber MandelbrotThread::getCritical()
{
    return critical;
}

void MandelbrotThread::setCritical(const ComplexNumber &value)
{
    critical = value;
}

double MandelbrotThread::getZoom()
{
    return zoom;
}

void MandelbrotThread::setZoom(double value)
{
    zoom = value;
}

QVector2D MandelbrotThread::getOffset()
{
    return offset;
}

void MandelbrotThread::setOffset(const QVector2D &value)
{
    offset = value;
}

QImage* MandelbrotThread::getImage()
{
    return image;
}

void MandelbrotThread::setImage(QImage *value)
{
    image = value;
}
MandelbrotThread::MandelbrotThread(QObject *parent) : QThread(parent)
{

}

void MandelbrotThread::run()
{
    drawMandelbrot(*image, iterations, offset, zoom, critical);
}

