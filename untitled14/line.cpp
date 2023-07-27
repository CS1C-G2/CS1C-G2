#include "line.h"

Line::Line(int id, int x1, int y1, int x2, int y2, QPen* pen) :
    Shape(id, LINE), x1{x1}, y1{y1}, x2{x2}, y2{y2}, pen{pen} { }
Line::~Line() {delete pen;}
void Line::draw() {
    update();
}
void Line::move(int x, int y) {
    int xDiff = x - x1;
    int yDiff = y - y1;
    x1 = x;
    y1 = y;
    x2 += xDiff;
    y2 += yDiff;
    draw();
}
double Line::area() {
    return 0;
}
double Line::perimeter() {
    return 0;
}
QRectF Line::boundingRect() const {
    return QRectF(x1, y1, x2 - x1, y2 - y1);
}
void Line::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(*pen);
    painter->drawLine(x1, y1, x2, y2);
}
