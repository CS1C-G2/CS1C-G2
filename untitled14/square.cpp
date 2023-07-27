#include "square.h"
Square::Square(int id, int x, int y, int length, QPen* pen, QBrush* brush) :
    Shape(id, SQUARE), x{x}, y{y}, length{length}, pen{pen}, brush{brush} { }
void Square::draw() {
    update();
}
void Square::move(int x, int y) {
    this->x = x;
    this->y = y;
    draw();
}
double Square::area() {
    return length * length;
}
double Square::perimeter() {
    return 4 * length;
}
QRectF Square::boundingRect() const {
    return QRectF(x, y, length, length);
}

void Square::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(*pen);
    painter->setBrush(*brush);
    painter->drawRect(x, y, length, length);
}
