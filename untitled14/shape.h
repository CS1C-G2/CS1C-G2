#ifndef SHAPE_H
#define SHAPE_H
#include "mainwindow.h"
#include "qgraphicsitem.h"
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
public:
    Shape() {id = 0;}

    Shape(int id) {this->id = id;}

    virtual ~Shape() = default;

    virtual void draw() = 0;

    virtual void move(int x, int y) = 0;

    virtual double area() = 0;

    virtual double perimeter() = 0;

private:
    int id;
    SHAPE_TYPES type;
};

#endif // SHAPE_H
