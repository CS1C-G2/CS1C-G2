#ifndef POLYGON_H
#define POLYGON_H
#include "shape.h"
class Polygon : public Shape, public QGraphicsItem
{
public:
    Polygon(int id, vector<int> x, vector<int> y, QPen* pen);

    void draw() override;

    void move(int x, int y) override;

    double area() override;

    double perimeter() override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

private:
    QPen* pen;
    QBrush brush;
    vector<int> x;
    vector<int> y;

};
#endif // POLYGON_H
