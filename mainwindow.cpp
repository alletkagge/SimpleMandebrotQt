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

    ui->sldIterations->setMaximum(colorCount);
    ui->spnIterations->setMaximum(colorCount);

    mainImage = QImage(imageSize, QImage::Format_Indexed8);
    mainImage.setColorTable(colors);
    mainImage.fill(Qt::black);
    //mainImage.fill(qRgb(0, 0, 0));
    MandelbrotThread::setIterations(iterations);
    MandelbrotThread::setCritical(ComplexNumber(0, 0));
    MandelbrotThread::setZoom(size);
    MandelbrotThread::setOffset(offset);
    MandelbrotThread::setImage(&mainImage);

    workThread = new MandelbrotThread();
    connect(workThread, SIGNAL(finished()), this, SLOT(workThreadFinished()));

    ui->lblImage->setPixmap(QPixmap::fromImage(mainImage));

    startRender();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sldIterations_valueChanged(int value)
{
    iterations = value;
    ui->spnIterations->setValue(value);
    MandelbrotThread::setIterations(iterations);
    startRender();
}

void MainWindow::on_sldOffsetX_valueChanged(int value)
{
    static int oldOffset = ui->sldOffsetX->sliderPosition();
    int relativeOffset = value - oldOffset;
    oldOffset = value;

    double offsetx = offset.x() + (20.0 * (double)relativeOffset / (double)ui->sldOffsetX->maximum() - 0.0) * size;
    offset.setX(offsetx);
    ui->lblOffsetX->setText(QString::number(offsetx));
    MandelbrotThread::setOffset(offset);
    //if(iterations < 50)
    startRender();
}

void MainWindow::on_sldOffsetY_valueChanged(int value)
{
    static int oldOffset = ui->sldOffsetY->sliderPosition();
    int relativeOffset = -(value - oldOffset);
    oldOffset = value;

    double offsety = offset.y() + (20.0 * (double)relativeOffset / (double)ui->sldOffsetY->maximum() - 0.0) * size;
    offset.setY(offsety);
    MandelbrotThread::setOffset(offset);
    ui->lblOffsetY->setText(QString::number(-offsety));
    //if(iterations < 50)
    startRender();
}

void MainWindow::on_sldZoom_valueChanged(int value)
{
    size = 1.0 - ((1.0 * (double)value / (double)ui->sldZoom->maximum() - 0.0));
    ui->spnZoom->setValue(1000.0 - size * 1000.0);
    MandelbrotThread::setZoom(size);
    //if(iterations < 50)
    startRender();
}

void MainWindow::on_btnRender_clicked()
{
    startRender();
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
    MandelbrotThread::setCritical(start);
    startRender();
}

void MainWindow::on_spnComplexImaginary_valueChanged(double arg1)
{
    start.imag() = (arg1);
    MandelbrotThread::setCritical(start);
    startRender();
}

void MainWindow::workThreadFinished()
{
    ui->lblImage->setPixmap(QPixmap::fromImage(mainImage));
}

void MainWindow::startRender()
{
    workThread->start();
}

