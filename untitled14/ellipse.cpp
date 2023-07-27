#include "ellipse.h"
Ellipse::Ellipse(int id, int x, int y, int radius1, int radius2,
                 QPen* pen, QBrush* brush) : Shape(id, ELLIPSE), x{x}, y{y},
    radius1{radius1}, radius2{radius2}, pen{pen},
    brush{brush} { }
void Ellipse::draw() {
    update();
}
void Ellipse::move(int x, int y) {
    this->x = x;
    this->y = y;
    draw();
}
double Ellipse::area() {
    return pi * radius1 * radius2;
}
double Ellipse::perimeter() {
    return  M_PI * (3 * (radius1 + radius2) - sqrt((3 * radius1 + radius2) * (radius1 + 3 * radius2)));
}
QRectF Ellipse::boundingRect() const {
    return QRectF(x, y, radius1 * 2, radius2 * 2);
}
void Ellipse::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(*pen);
    painter->setBrush(*brush);
    painter->drawEllipse(x, y, radius1, radius2);
}
