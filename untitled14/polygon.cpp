#include "polygon.h"
Polygon::Polygon(int id, myStd::vector<int> x, myStd::vector<int> y, QPen* pen, QBrush* brush) :
    Shape(id, POLYGON), x{x}, y{y}, pen{pen}, brush{brush} { }
void Polygon::draw() {
    update();
}
void Polygon::move(int x, int y) {
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
double Polygon::area() {
    int numPoints = x.size();
    for(int i = 0; i < x.size(); i++) {
        //Calculate length of sides. Can just copy code from perimeter
    }
    return 0;
}
double Polygon::perimeter() {
    double perim;
    for(int i = 0; i < x.size()-1; i++) {
        perim += sqrt(pow(x[i+1] - x[i], 2) + pow(y[i+1] - y[i], 2));
    }
    perim += sqrt(pow(x[0] - x.back(), 2) + pow(y[0] - y.back(), 2));
    return perim;
}
QRectF Polygon::boundingRect() const {
    return QRectF();
}
void Polygon::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    const int SIZE = x.size();
    QPointF points[SIZE];
    for(int i = 0; i < SIZE; i++) {
        points[i] = QPointF(x[i], y[i]);
    }
    painter->setPen(*pen);
    painter->setBrush(*brush);
    painter->drawPolygon(points, 4);
}
