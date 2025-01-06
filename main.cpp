#include<functional>
#include"libOne.h"
//関数(function)
double func0(double x) { return x; }
double func1(double x) { return x * x; }
double func2(double x) { return x * x * x; }
double func3(double x) { return cos(x); }

//関数グラフ
void graph(std::function<double(double)> f)
{
    strokeWeight(5);
    stroke(255, 120, 120);

    double h = 0.1f;
    for (double x = minScaleX(); x < maxScaleX(); x += h)
    {
        mathLine(x, f(x), x + h, f(x + h));
    }
}
void points(std::function<double(double)> f, double x, double h)
{
    //２つの点
    strokeWeight(20);
    mathPoint(x, f(x));
    mathPoint(x + h, f(x + h));

    //２つの点の情報
    textSize(25);
    strokeWeight(1);
    fill(255);
    mathLine(x, f(x), x, 0); mathText("x", x, 0);
    fill(255, 120, 120);
    mathLine(x, f(x), 0, f(x)); mathText("f(x)", 0, f(x));
    if (h > 0.0000001) {
        fill(255);
        mathLine(x + h, f(x + h), x + h, 0); mathText("x+h", x + h, 0);
        fill(255, 120, 120);
        mathLine(x + h, f(x + h), 0, f(x + h)); mathText("f(x+h)", 0, f(x + h));
    }
    //テキスト情報
    printSize(40);
    fill(255); print((let)"x=" + x);
    fill(255, 120, 120); print((let)"f(x)=" + f(x));
    print("");
    fill(150); print((let)"h=" + h + "←Q-Eキーで変化");
    fill(255); print((let)"x+h=" + (x + h));
    fill(255, 120, 120); print((let)"f(x+h)=" + f(x + h));
    print("");
}
void line(std::function<double(double)> f, double x, double h)
{
    //傾き
    double a = (f(x + h) - f(x)) / h;
    //切片
    double b = f(x) - a * x;
    //直線
    float sx = minScaleX();
    float sy = a * sx + b;
    float ex = maxScaleX();
    float ey = a * ex + b;
    strokeWeight(5);
    stroke(255, 255, 120);
    mathLine(sx, sy, ex, ey);
    //テキスト情報
    fill(255, 255, 120); print((let)"(f(x + h) - f(x)) / h = " + a);
}
void pointline(std::function<double(double)> f, double x, double h)
{
    //２つの点
    strokeWeight(20);
    mathPoint(x, f(x));
    textSize(25);
    strokeWeight(1);
    fill(255);
    mathLine(x, f(x), x, 0); mathText("x", x, 0);
    fill(255, 120, 120);
    mathLine(x, f(x), 0, f(x)); mathText("f(x)", 0, f(x));
    //テキスト情報
    printSize(40);
    fill(255); print((let)"x=" + x);
    fill(255, 120, 120); print((let)"f(x)=" + f(x));
    print("");

    //傾き
    double a = (f(x + h) - f(x)) / h;
    //切片
    double b = f(x) - a * x;
    //直線
    float sx = minScaleX();
    float sy = a * sx + b;
    float ex = maxScaleX();
    float ey = a * ex + b;
    strokeWeight(5);
    stroke(255, 255, 120);
    mathLine(sx, sy, ex, ey);
    //テキスト情報
    fill(255, 255, 120); print((let)"(f(x + h) - f(x)) / h = " + a);
}

void gmain()
{
    window(1920, 1080, full);

    float ox = 960;
    float oy = 720;
    float unit = 160;

    //点のｘ座標
    double x = 1;
    //ｘの変化量
    double h = 1;

    //関数ポインタ
    std::function<double(double)> f = &func1;
    int sw = 1;
    int dispSw = 2;
    while (notQuit)
    {
        //関数切り替え
        if (isTrigger(KEY_SPACE))
        {
            ++sw %= 4;
            switch (sw)
            {
            case 0: f = &func0; break;
            case 1: f = &func1; break;
            case 2: f = &func2; break;
            case 3: f = &func3; break;
            }
        }
        //点ｘ座標
        if (isPress(KEY_D))x += 0.01;
        if (isPress(KEY_A))x -= 0.01;
        if (isTrigger(KEY_H))x += 0.01;
        if (isTrigger(KEY_F))x -= 0.01;
        //ｈ(xの変化量)
        if (isPress(KEY_E))h += 0.01;
        if (isPress(KEY_Q))h -= 0.01;
        if (isTrigger(KEY_Y))h += 0.01;
        if (isTrigger(KEY_R))h -= 0.01;
        if (h <= 0)h = 0.0000001;
        //描画
        clear(); fill(30); noStroke(); rect(0, 0, width, height);
        if (isPress(KEY_L))ox += 1;
        if (isPress(KEY_J))ox -= 1;
        if (isPress(KEY_I))oy -= 1;
        if (isPress(KEY_K))oy += 1;
        if (isPress(KEY_O))unit += 1;
        if (isPress(KEY_U))unit -= 1;
        mathAxis(ox, oy, unit, 255);

        if (isTrigger(KEY_X))++dispSw %= 4;
        switch (dispSw) {
        case 0:graph(f); break;
        case 1:graph(f); points(f, x, h); break;
        case 2:graph(f); points(f, x, h); line(f, x, h); break;
        case 3:graph(f); pointline(f, x, h); break;
        }
    }
}
