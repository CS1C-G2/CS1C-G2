#ifndef SQUARE_H
#define SQUARE_H
#include "Shape.h"
class Square : public Shape, public QGraphicsItem
{
public:
    Square(int id, int x, int y, int length, QPen* pen, QBrush* brush);

    void draw() override;

    void move(int x, int y) override;

    double area() override;

    double perimeter() override;

    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    Qt::GlobalColor PenColor;
    QPen* pen;
    QBrush* brush;
    int x;
    int y;
    int length;
};
#endif // SQUARE_H
