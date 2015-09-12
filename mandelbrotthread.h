#ifndef MANDELBROTTHREAD_H
#define MANDELBROTTHREAD_H

#include <QThread>
#include <QVector2D>
#include <QImage>

#include "complexnumber.h"

class MandelbrotThread : public QThread
{
    static int iterations;
    static ComplexNumber critical;
    static double zoom;
    static QVector2D offset;
    static QImage *image;
    Q_OBJECT
public:
    MandelbrotThread(QObject *parent = 0);
    void run();
    static int getIterations();
    static void setIterations(int value);
    static ComplexNumber getCritical();
    static void setCritical(const ComplexNumber &value);
    static double getZoom();
    static void setZoom(double value);
    static QVector2D getOffset();
    static void setOffset(const QVector2D &value);
    static QImage *getImage();
    static void setImage(QImage *value);
};

#endif // MANDELBROTTHREAD_H
