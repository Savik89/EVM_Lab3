#include "graphics.h"
#include <cmath>
#include <iostream>

#pragma comment(lib, "graphics.lib")

// (cos(x/4))^2+sqrt(x) | 3π/2 | 16π |

double x0 = 4.71; // 3π/2
double xn = 50.24; // 16π
int currentPointX = 130, currentPointY = 500;

void drawFunction()
{
    double Fmax(0), F;
    double x;
    double coefficient = 30;
    int i = 0, imax = 0;

    for (i = 1, x = x0; x <= xn; i++, x += 0.1){
        F = (pow(cos(x / 4), 2) + sqrt(x));
        if (F > Fmax) {
            Fmax = F;
            imax = i;
        }
        putpixel(currentPointX + i, (currentPointY - F * coefficient), GREEN);
        delay(10);
    }

    int newCurrX = currentPointX - x0 * 10; // координата х в пикселях для оси F(x)
    char FmaxInGraphic[5]{ "Fmax" };
    setlinestyle(DOTTED_LINE, 1, 1);
    line(currentPointX + imax, (currentPointY - Fmax * coefficient), newCurrX, (currentPointY - Fmax * coefficient));// горизонтальный пунктир от Fmax
    line(currentPointX + imax, (currentPointY - Fmax * coefficient), currentPointX + imax, currentPointY);// вертикальный пунктир от Fmax
    outtextxy(currentPointX + imax, (currentPointY - Fmax * coefficient) - 25, FmaxInGraphic);

    setlinestyle(SOLID_LINE, 1, 1);
    setcolor(GREEN);
    char res[20];
    sprintf_s(res, "Fmax = %f", Fmax);
    outtextxy(360, 110, res); // вывод текста 'Fmax = '
    rectangle(330, 95, 500, 140); // координаты прямоугольника в котором выводится 'Fmax = '
}

void drawGraphic(int maxX, int maxY)
{
    char zero[2]{ "0" };
    char Fx[5]{ "F(x)" };
    char x[2]{ "x" };
    setcolor(BLACK);
    setlinestyle(SOLID_LINE, 1, 1); // сплошная линия

    int newCurrX = currentPointX - x0 * 10;
    line(newCurrX, maxY, newCurrX, currentPointY); // ocь Х
    line(newCurrX, currentPointY, maxX, currentPointY); // ось F(x)

    setcolor(BLACK);
    outtextxy(newCurrX - 5, maxY - 20, Fx);
    outtextxy(maxX + 15, currentPointY - 5, x);

    setcolor(BLACK);
    line(newCurrX, maxY, newCurrX - 7, maxY + 7); // левая линия стрелки на оси Х
    line(newCurrX, maxY, newCurrX + 7, maxY + 7); // правая линия стрелки на оси Х

    line(maxX, currentPointY, maxX - 7, currentPointY - 7); // левая линия стрелки на оси F(x)
    line(maxX, currentPointY, maxX - 7, currentPointY + 7); // правая линия стрелки на оси F(x)

    outtextxy(newCurrX - 20, currentPointY, zero);

    for (int i = 1; i < 16; i++) {
        line(newCurrX - 5, currentPointY - i * 15, newCurrX + 5, currentPointY - i * 15); // риски на оси F(x)
    }
    for (int i = 1; i < 34; i++) {
        line(newCurrX + 20 * i, currentPointY - 5, newCurrX + 20 * i, currentPointY + 5); // риски на оси x
    }
    char valueX[3];
    char valueY[3];
    int val = 1;
    for (int i = 2; i < 16; i += 2) {
        sprintf_s(valueY, "%d", val);
        val++;
        outtextxy(newCurrX - 20, currentPointY - i * 15 - 5, valueY); // числа на оси F(x)
    }
    for (int i = 4; i <= 64; i += 4) {
        sprintf_s(valueX, "%d", i);
        outtextxy(newCurrX + 18 * i / 2 + i - 3, currentPointY + 7, valueX); // числа на оси X
    }
}

int main()
{
    initwindow(900, 600); // initialize graphics window at 900 x 600
    setbkcolor(WHITE);
    cleardevice(); // заполняет этим цветом всё окно

    int maxX = getmaxx();
    int maxY = getmaxy();

    int newX = maxX - currentPointX;
    int newY = maxY - 350;

    setcolor(BLACK);
    char expression[29]{ "F = (cos(x / 4))^2 + sqrt(x)" };
    outtextxy(340, 50, expression);

    drawGraphic(newX, newY);
    drawFunction();

    getch();
    return 0;
}
