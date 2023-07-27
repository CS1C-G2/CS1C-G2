#include "rectangle.h"
Rectangle::Rectangle(int id, int x, int y, int length, int width, QPen* pen, QBrush* brush) :
    Shape(id, RECTANGLE), x{x}, y{y}, length{length}, width{width}, pen{pen}, brush{brush} { }
void Rectangle::draw() {
    update();
}
void Rectangle::move(int x, int y) {
    this->x = x;
    this->y = y;
    draw();
}
double Rectangle::area() {
    return length * width;
}
double Rectangle::perimeter() {
    return (length * 2) + (width * 2);
}
QRectF Rectangle::boundingRect() const {
    return QRectF(x, y, length, length);
}
void Rectangle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(*pen);
    painter->setBrush(*brush);
    painter->drawRect(x, y, length, width);
}
