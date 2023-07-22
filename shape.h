#ifndef SHAPE_H
#define SHAPE_H
#include "mainwindow.h"
#include <QMainWindow>
#include <QMainWindow>
#include <QPainter>
#include <QPaintEvent>
#include <QColor>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <vector>
#include <cmath>
#include <QFont>
using namespace std;
const double pi = 3.14;
enum SHAPE_TYPES { LINE, POLYLINE, POLYGON, RECTANGLE, SQUARE, ELLIPSE, CIRCLE, TEXT };

class Shape
{
private:
    int id;
    SHAPE_TYPES type;
public:
    virtual void draw() = 0;
    virtual void move(int x, int y) = 0;
    virtual double area() = 0;
    virtual double perimeter() = 0;
};

class Line : public Shape, public QWidget
{
public:
    Line(int x1, int y1, int x2, int y2, QPen* pen) {
        this->pen = new QPen;
        this->pen = pen;
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    }
    ~Line() {delete pen;}
    void draw() override {
        update();
    }
    void move(int x, int y) override {
        int xDiff = x1 - x;
        int yDiff = y1 - y;
        x1 = x;
        y1 = y;
        x2 += xDiff;
        y2 += yDiff;
        draw();
    }
    double area() override {
        return 0;
    }
    double perimeter() override {
        return 0;
    }
    void paintEvent(QPaintEvent* event) override {
        Q_UNUSED(event); // this is confusing but what this will do is it will to suppress the "unused variable" compiler warning
        QPainter painter(this); // painting
        painter.setPen(*pen);
        painter.drawLine(x1, y1, x2, y2);
    }


private:
    QPen* pen;
    int x1;
    int y1;
    int x2;
    int y2;
};

class Polyline : public Shape, public QWidget
{
public:
    Polyline(vector<int> x, vector<int> y, QPen* pen, QBrush* brush) :
        x{x}, y{y}, pen{new QPen}, brush{new QBrush} {
        this->pen = pen;
        this->brush = brush;
    }
    void draw() override {
        update();
    }
    void move(int x, int y) override {
        int xDiff = this->x[0] - x;
        int yDiff = this->y[0] - y;
        this->x[0] = x;
        this->y[0] = y;
        for(int i = 1; i < this->x.size(); i++) {
            this->x[i] += xDiff;
            this->y[i] += yDiff;
        }
        draw();
    }
    double area() override {
        return 0;
    }
    double perimeter() override {
        return 0;
    }
    void paintEvent(QPaintEvent* event) override {
        Q_UNUSED(event); // this is confusing but what this will do is it will to suppress the "unused variable" compiler warning
        QPainter painter(this); // painting
        painter.setPen(*pen);
        painter.setBrush(*brush);
        const int SIZE = x.size();
        QPointF points[SIZE];
        for(int i = 0; i < SIZE; i++) {
            points[i] = QPointF(x[i], y[i]);
        }
        painter.drawPolyline(points, SIZE);
    }

private:
    Qt::GlobalColor PenColor;
    QPen* pen;
    QBrush* brush;
    vector<int> x;
    vector<int> y;

};

class Polygon : public Shape, public QWidget
{
private:
    QPen* pen;
    QBrush brush;
    vector<int> x;
    vector<int> y;
public:
    Polygon(vector<int> x, vector<int> y, QPen* pen) {
        pen = new QPen;
        this->x = x;
        this->y = y;
        this->pen = pen;
    }
    void draw() override {
        update();
    }
    void move(int x, int y) override {
        int xDiff = this->x[0] - x;
        int yDiff = this->y[0] - y;
        this->x[0] = x;
        this->y[0] = y;
        for(int i = 1; i < this->x.size(); i++) {
            this->x[i] += xDiff;
            this->y[i] += yDiff;
        }
        draw();
    }
    double area() override {
        int numPoints = x.size();
        for(int i = 0; i < x.size(); i++) {
            //Calculate length of sides. Can just copy code from perimeter
        }
        return 0;
    }
    double perimeter() override {
        double perim;
        for(int i = 0; i < x.size()-1; i++) {
            perim += sqrt(pow(x[i+1] - x[i], 2) + pow(y[i+1] - y[i], 2));
        }
        perim += sqrt(pow(x[0] - x.back(), 2) + pow(y[0] - y.back(), 2));
        return perim;
    }
    void paintEvent(QPaintEvent* event) override {
        Q_UNUSED(event); // this is confusing but what this will do is it will to suppress the "unused variable" compiler warning
        QPainter painter(this); // painting
        const int SIZE = x.size();
        QPointF points[SIZE];
        for(int i = 0; i < SIZE; i++) {
            points[i] = QPointF(x[i], y[i]);
        }
        painter.setPen(*pen);
        painter.drawPolygon(points, 4);
    }

};
class Rectangle : public Shape, public QWidget
{
public:
    Rectangle(int x1, int y1, int length, int width, QPen* pen, QBrush* brush, QWidget *parent = nullptr) :
        QWidget(parent), x1{x1}, y1{y1}, length{length}, width{width}, pen{new QPen}, brush{new QBrush} {
        this->pen = pen;
        this->brush = brush;
    }
    void draw() override {
        update();
    }
    void move(int x, int y) override {
        x1 = x;
        y1 = y;
        draw();
    }
    double area() override {
        return length * width;
    }
    double perimeter() override {
        return (length * 2) + (width * 2);
    }
    void paintEvent(QPaintEvent* event) override {
        Q_UNUSED(event); // this is confusing but what this will do is it will to suppress the "unused variable" compiler warning
        QPainter painter(this); // painting
        painter.setPen(*pen);
        painter.setBrush(*brush);
        painter.drawRect(x1, y1, length, width);
    }
private:
    Qt::GlobalColor PenColor;
    QPen* pen;
    QBrush* brush;
    int x1;
    int y1;
    int length;
    int width;
};
class Square : public Shape, public QWidget
{
public:
    Square(int x, int y, int length, QPen* pen, QBrush* brush) :
        x{x}, y{y}, length{length}, pen{new QPen}, brush{new QBrush} {
        this->pen = pen;
        this->brush = brush;
    }
    void draw() override {
        update();
    }
    void move(int x, int y) override {
        this->x = x;
        this->y = y;
        draw();
    }
    double area() override {
        return length * length;
    }
    double perimeter() override {
        return 4 * length;
    }
    void paintEvent(QPaintEvent* event) override {
        Q_UNUSED(event); // this is confusing but what this will do is it will to suppress the "unused variable" compiler warning
        QPainter painter(this); // painting
        painter.setPen(*pen);
        painter.setBrush(*brush);
        painter.drawRect(x, y, length, length);
    }
private:
    Qt::GlobalColor PenColor;
    QPen* pen;
    QBrush* brush;
    int x;
    int y;
    int length;
};
class Ellipse : public Shape, public QWidget
{
public:
    Ellipse(int x, int y, int radius1, int radius2,
            QPen* pen, QBrush* brush) : x{x}, y{y},
        radius1{radius1}, radius2{radius2}, pen{new QPen},
        brush{new QBrush}
    {
        this->pen = pen;
        this->brush = brush;
    }
    void draw() override {
        update();
    }
    void move(int x, int y) override {
        this->x = x;
        this->y = y;
        draw();
    }
    double area() override {
        return pi * radius1 * radius2;
    }
    double perimeter() override {
        double perimeter = M_PI * (3 * (width + height) - sqrt((3 * width + height) * (width + 3 * height)));
        return perimeter;
    }
    void paintEvent(QPaintEvent* event) override {
        Q_UNUSED(event); // this is confusing but what this will do is it will to suppress the "unused variable" compiler warning
        QPainter painter(this); // painting
        painter.setPen(*pen);
        painter.setBrush(*brush);
        painter.drawEllipse(x, y, radius1, radius2);
    }
private:
    Qt::GlobalColor PenColor;
    QPen* pen;
    QBrush* brush;
    int x;
    int y;
    int radius1;
    int radius2;
};
class Circle : public Shape, public QWidget
{
public:
    Circle(int x, int y, int radius, QPen* pen, QBrush* brush) :
        x{x}, y{y}, radius{radius}, pen{new QPen}, brush{new QBrush}
    {
        this->pen = pen;
        this->brush = brush;
    }
    void draw() override {
        update();
    }
    void move(int x, int y) override {
        this->x = x;
        this->y = y;
        draw();
    }
    double area() override {
        return pi * pow(radius, 2);
    }
    double perimeter() override {
        return 2 * pi * radius;
    }
    void paintEvent(QPaintEvent* event) override {
        Q_UNUSED(event); // this is confusing but what this will do is it will to suppress the "unused variable" compiler warning
        QPainter painter(this); // painting
        painter.setPen(*pen);
        painter.setBrush(*brush);
        painter.drawEllipse(x, y, radius, radius);
    }

private:
    Qt::GlobalColor PenColor;
    QPen* pen;
    QBrush* brush;
    int x;
    int y;
    int radius;
};
class Text : public Shape
{
public:
    Text(int x1, int y1, int w, int l, QString textString, QFont* font, QPen* pen, Qt::AlignmentFlag textAlignment) : x1{x1}, y1{y1}, w{w}, l{l}, textString{textString}, textAlignment{textAlignment} {
        this->font = font;
        this->pen = pen;
    }

    ~Text() override {}

    void draw() override {
        update();
    }

    void move(int x, int y) override {
        x1 = x;
        y1 = y;
        draw();
    }

    double area() override {
        return l * w;
    }

    double perimeter() override {
        return (l * 2) + (w * 2);
    }

    void paintEvent(QPaintEvent* event) override {
        Q_UNUSED(event); // this is confusing but what this will do is it will to suppress the "unused variable" compiler warning
        QPainter painter(this); // painting
        painter.setFont(*font);
        painter.setPen(*pen);
        painter.drawText(x1, y1, w, l, textAlignment, textString);
    }

    void setWidth(int width)
    {
        w = width;
    }

    void setLenth(int length)
    {
        l = length;
    }

    void setTextString(QString textString)
    {
        this->textString = textString;
    }

    void setTextColor(Qt::GlobalColor textColor)
    {
        pen->setColor(textColor);
    }

    void setTextAlignment(Qt::AlignmentFlag textAlignment)
    {
        this->textAlignment = textAlignment;
    }

    void setTextPointSize(int textPointSize)
    {
        font->setPointSize(textPointSize);
    }

    void setTextFontFamily(QString textFontFamily)
    {
        font->setFamily(textFontFamily);
    }

    void setTextFontStyle(QFont::Style textFontStyle)
    {
        font->setStyle(textFontStyle);
    }

    void setTextFontWeight(QFont::Weight textFontWeight)
    {
        font->setWeight(textFontWeight);
    }

private:
    int x1;
    int y1;
    int w;
    int l;
    QString textString;
    QFont* font;
    QPen* pen;
    Qt::AlignmentFlag textAlignment;

};
#endif // SHAPE_H
