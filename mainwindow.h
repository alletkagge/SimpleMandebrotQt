#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector2D>
#include <QSize>
#include <QVector>
#include <QRgb>

#include <cmath>

#include "complexnumber.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_sldIterations_valueChanged(int value);

    void on_sldOffsetX_valueChanged(int value);

    void on_sldOffsetY_valueChanged(int value);

    void on_sldZoom_valueChanged(int value);

    void on_btnRender_clicked();

    void on_spnZoom_valueChanged(double arg1);

    void on_spnIterations_valueChanged(int arg1);

    void on_spnComplexReal_valueChanged(double arg1);

    void on_spnComplexImaginary_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
    int iterations;
    QVector2D offset;
    QSize imageSize;
    double size;
    QVector<QRgb> colors;
    ComplexNumber start;
};

#endif // MAINWINDOW_H
