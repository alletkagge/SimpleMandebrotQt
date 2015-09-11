#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QImage>
#include <QPainter>

#include <QVector2D>

#include <QDebug>

#include <cmath>

#include "mandelbrot.h"

//#include "mandelbrotthread.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    iterations = 8;
    offset = QVector2D(0, 0);
    size = 1.0;
    imageSize = QSize(400, 400);
    start = ComplexNumber(0,0);

    //generate colortable with 256 colors for indexed image
    int colorCount = 1 << 8;
    for(int i = 0; i < colorCount; ++i)
    {
        //colors.append(qRgb(((2*i*i*i*i + 5*i*i*i -2*i*i + 8*i - 128) % 256), ((2 * i*i + 4) % 256), ((32*i*i*i + 32) % 256)));
        colors.append(qRgb(((i) % 32) * 8, ((i) % 64) * 4, ((i) % 128) * 2));
    }
    colors.append(qRgb(0, 0, 0));
/*
    MandelbrotThread::setIterations(iterations);
    MandelbrotThread::setCritical(ComplexNumber(0, 0));
    MandelbrotThread::setSize(size);
    MandelbrotThread::setOffset(offset);
    MandelbrotThread::setColorTable(colors);
    MandelbrotThread::setImageSize(imageSize);
    MandelbrotThread::setXtiles(2);
    MandelbrotThread::setYtiles(1);
*/
    ui->sldIterations->setMaximum(colorCount);
    ui->spnIterations->setMaximum(colorCount);

    mainImage = QImage(imageSize, QImage::Format_Indexed8);
    mainImage.setColorTable(colors);
    mainImage.fill(qRgb(0, 0, 0));

    ui->btnRender->click();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sldIterations_valueChanged(int value)
{
    iterations = value;
    ui->spnIterations->setValue(value);
    ui->btnRender->click();
}

void MainWindow::on_sldOffsetX_valueChanged(int value)
{
    static int oldOffset = ui->sldOffsetX->sliderPosition();
    int relativeOffset = value - oldOffset;
    oldOffset = value;

    double offsetx = offset.x() + (20.0 * (double)relativeOffset / (double)ui->sldOffsetX->maximum() - 0.0) * size;
    offset.setX(offsetx);
    ui->lblOffsetX->setText(QString::number(offsetx));
    //if(iterations < 50)
    ui->btnRender->click();
}

void MainWindow::on_sldOffsetY_valueChanged(int value)
{
    static int oldOffset = ui->sldOffsetY->sliderPosition();
    int relativeOffset = -(value - oldOffset);
    oldOffset = value;

    double offsety = offset.y() + (20.0 * (double)relativeOffset / (double)ui->sldOffsetY->maximum() - 0.0) * size;
    offset.setY(offsety);
    ui->lblOffsetY->setText(QString::number(-offsety));
    //if(iterations < 50)
    ui->btnRender->click();
}

void MainWindow::on_sldZoom_valueChanged(int value)
{
    size = 1.0 - ((1.0 * (double)value / (double)ui->sldZoom->maximum() - 0.0));
    ui->spnZoom->setValue(1000.0 - size * 1000.0);
    //if(iterations < 50)
    ui->btnRender->click();
}

void MainWindow::on_btnRender_clicked()
{
    drawMandelbrot(mainImage, iterations, offset, size, start);
    ui->lblImage->setPixmap(QPixmap::fromImage(mainImage));
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
    start.real() = (arg1);
    ui->btnRender->click();
}

void MainWindow::on_spnComplexImaginary_valueChanged(double arg1)
{
    start.imag() = (arg1);
    ui->btnRender->click();
}

