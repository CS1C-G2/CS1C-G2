#include "polyline.h"
Polyline::Polyline(int id, myStd::vector<int> x, myStd::vector<int> y, QPen* pen) :
    Shape(id, POLYLINE), x{x}, y{y}, pen{pen} { }
void Polyline::draw() {
    update();
}
void Polyline::move(int x, int y) {
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
double Polyline::area() {
    return 0;
}
double Polyline::perimeter() {
    return 0;
}
QRectF Polyline::boundingRect() const {
    return QRectF();
}
void Polyline::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(*pen);
    const int SIZE = x.size();
    QPointF points[SIZE];
    for(int i = 0; i < SIZE; i++) {
        points[i] = QPointF(x[i], y[i]);
    }
    painter->drawPolyline(points, SIZE);
}
