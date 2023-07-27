#ifndef POLYLINE_H
#define POLYLINE_H
#include "Shape.h"

class Polyline : public Shape, public QGraphicsItem
{
public:
    Polyline(int id, myStd::vector<int> x, myStd::vector<int> y, QPen* pen);

    void draw() override;

    void move(int x, int y) override;

    double area() override;

    double perimeter() override;

    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    Qt::GlobalColor PenColor;
    QPen* pen;
    myStd::vector<int> x;
    myStd::vector<int> y;

};
#endif // POLYLINE_H
