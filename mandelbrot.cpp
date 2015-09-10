#include "mandelbrot.h"

ComplexNumber mandelbrot(ComplexNumber z, ComplexNumber c)
{
    return z * z + c;
}

void drawMandelbrot(QImage & image, int iterations, QVector2D offset, double size, ComplexNumber critical)
{
    ComplexNumber fz, c;
    double rx, ry;
    float color = 0.0;
    int wx = image.width(), wy = image.height();
    int byteOffset = image.bytesPerLine() / image.width();
    for(int y = 0; y < wy; ++y)
    {
        uchar *scanline = image.scanLine(y);
        for(int x = 0; x < wx; x++)
        {
            rx = (2.0 * ((double)x / (double)wx) - 1.0);
            ry = (2.0 * ((double)y / (double)wy) - 1.0);
            c = ComplexNumber(rx * size + offset.x(), ry * size + offset.y());
            fz = critical;
            //qDebug() << "x: " << z << ", y: " << c;
            //fz = mandelbrot(fz, c);
            int i = 0;
            for(i = 0; i < iterations && fz.value() <= 2.0; ++i)
            {
                fz = mandelbrot(fz, c);
            }
            color = (float)i / (float)iterations;
            if(image.format() == QImage::Format_RGB888)
            {
                *(scanline + x * byteOffset) = 255 * color;
                *(scanline + x * byteOffset + 1) = 255 * color;
                *(scanline + x * byteOffset + 2) = 255 * color;
            }

            if(image.format() == QImage::Format_Indexed8)
            {
                *(scanline + x * byteOffset) = i % (image.colorCount() + 1);// * color;
            }
            //image.setPixel(x, y, qRgb(i % 256, i % 256, i % 256));
            //image.setPixel(x, y, i % 256);
        }
    }
}
