#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QImage>
#include <QPainter>

#include <QVector2D>

#include <QDebug>

#include <cmath>

#include "mandelbrot.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //f(z) = z^2 + c <= 2

    iterations = 8;
    offset = QVector2D(0, 0);
    size = 1.0;
    imageSize = QSize(400, 400);
    start = ComplexNumber(0,0);

    //QVector<QRgb> colors;
    int colorCount = 1 << 10;
    for(int i = 0; i < colorCount; ++i)
    {
        colors.append(qRgb(((2*i*i*i*i - 128) % 256), ((2 * i*i + 4) % 256), ((32*i*i*i + 32) % 256)));
    }
    colors.append(qRgb(0, 0, 0));

    ui->sldIterations->setMaximum(colorCount);
    ui->spnIterations->setMaximum(colorCount);

    QImage mandel = QImage(imageSize, QImage::Format_Indexed8);
    mandel.setColorTable(colors);
    mandel.fill(qRgb(0, 0, 0));

    drawMandelbrot(mandel, iterations, offset, size);

    ui->lblImage->setPixmap(QPixmap::fromImage(mandel));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sldIterations_valueChanged(int value)
{
    iterations = value;
    ui->spnIterations->setValue(value);
}

void MainWindow::on_sldOffsetX_valueChanged(int value)
{
    static int oldOffset = ui->sldOffsetX->sliderPosition();
    int relativeOffset = value - oldOffset;
    oldOffset = value;

    double offsetx = offset.x() + (20.0 * (double)relativeOffset / (double)ui->sldOffsetX->maximum() - 0.0) * size;
    //(40.0 * (double)value / (double)ui->sldOffsetX->maximum() - 20.0)
    offset.setX(offsetx);
    ui->lblOffsetX->setText(QString::number(offsetx));
    //offset.setX((40.0 * (double)value / (double)ui->sldOffsetX->maximum() - 20.0) * size);
    if(iterations < 50) ui->btnRender->click();
}

void MainWindow::on_sldOffsetY_valueChanged(int value)
{
    static int oldOffset = ui->sldOffsetY->sliderPosition();
    int relativeOffset = -(value - oldOffset);
    oldOffset = value;

    double offsety = offset.y() + (20.0 * (double)relativeOffset / (double)ui->sldOffsetY->maximum() - 0.0) * size;
    //(40.0 * (double)value / (double)ui->sldOffsetX->maximum() - 20.0)
    offset.setY(offsety);
    ui->lblOffsetY->setText(QString::number(offsety));
    //offset.setY((40.0 * (double)value / (double)ui->sldOffsetY->maximum() - 20.0) * size);
    if(iterations < 50) ui->btnRender->click();
}

void MainWindow::on_sldZoom_valueChanged(int value)
{
    size = 2.0 - ((2.0 * (double)value / (double)ui->sldZoom->maximum() - 0.0));
    ui->spnZoom->setValue(1000.0 - size * 500.0);
    if(iterations < 50) ui->btnRender->click();
}

void MainWindow::on_btnRender_clicked()
{
    QImage mandel = QImage(imageSize, QImage::Format_Indexed8);
    mandel.setColorTable(colors);
    //mandel.fill(qRgb(0, 0, 0));
    drawMandelbrot(mandel, iterations, offset, size, start);
    ui->lblImage->setPixmap(QPixmap::fromImage(mandel));
}

void MainWindow::on_spnZoom_valueChanged(double arg1)
{
    ui->sldZoom->setValue((ui->sldZoom->maximum() * (arg1 * 0.001)));
}

void MainWindow::on_spnIterations_valueChanged(int arg1)
{
    ui->sldIterations->setValue(arg1);
}

void MainWindow::on_spnComplexReal_valueChanged(double arg1)
{
    start.setReal(arg1);
    ui->btnRender->click();
}

void MainWindow::on_spnComplexImaginary_valueChanged(double arg1)
{
    start.setImaginary(arg1);
    ui->btnRender->click();
}
