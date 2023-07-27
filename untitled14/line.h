#ifndef LINE_H
#define LINE_H
#include "Shape.h"

class Line : public Shape, public QGraphicsItem
{
public:
    Line(int id, int x1, int y1, int x2, int y2, QPen* pen);

    ~Line();

    void draw() override;

    void move(int x, int y) override;

    double area() override;

    double perimeter() override;

    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;


private:
    QPen* pen;
    int x1;
    int y1;
    int x2;
    int y2;
};
#endif // LINE_H
