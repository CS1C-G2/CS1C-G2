#ifndef POLYGON_H
#define POLYGON_H
#include "Shape.h"
class Polygon : public Shape, public QGraphicsItem
{
public:
    Polygon(int id, myStd::vector<int> x, myStd::vector<int> y, QPen* pen, QBrush* brush);

    void draw() override;

    void move(int x, int y) override;

    double area() override;

    double perimeter() override;

    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

private:
    QPen* pen;
    QBrush* brush;
    myStd::vector<int> x;
    myStd::vector<int> y;

};
#endif // POLYGON_H
