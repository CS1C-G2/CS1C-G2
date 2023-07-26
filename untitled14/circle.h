#ifndef CIRCLE_H
#define CIRCLE_H
#include "shape.h"
class Circle : public Shape, public QGraphicsItem
{
public:
    Circle(int id, int x, int y, int radius, QPen* pen, QBrush* brush);
    void draw() override;
    void move(int x, int y) override;
    double area() override;
    double perimeter() override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    Qt::GlobalColor PenColor;
    QPen* pen;
    QBrush* brush;
    int x;
    int y;
    int radius;
};
#endif // CIRCLE_H
