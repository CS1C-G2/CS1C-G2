#ifndef POLYLINE_H
#define POLYLINE_H
#include "shape.h"

class Polyline : public Shape, public QGraphicsItem
{
public:
    Polyline(int id, vector<int> x, vector<int> y, QPen* pen, QBrush* brush);

    void draw() override;

    void move(int x, int y) override;

    double area() override;

    double perimeter() override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    Qt::GlobalColor PenColor;
    QPen* pen;
    QBrush* brush;
    vector<int> x;
    vector<int> y;

};
#endif // POLYLINE_H
