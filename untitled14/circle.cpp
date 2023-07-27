#include "circle.h"
Circle::Circle(int id, int x, int y, int radius, QPen* pen, QBrush* brush) :
    Shape(id, CIRCLE), x{x}, y{y}, radius{radius}, pen{pen}, brush{brush} { }
void Circle::draw() {
    update();
}
void Circle::move(int x, int y) {
    this->x = x;
    this->y = y;
    draw();
}
double Circle::area() {
    return pi * pow(radius, 2);
}
double Circle::perimeter() {
    return 2 * pi * radius;
}
QRectF Circle::boundingRect() const {
    return QRectF(x, y, radius * 2, radius * 2);
}
void Circle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(*pen);
    painter->setBrush(*brush);
    painter->drawEllipse(x, y, radius, radius);
}
