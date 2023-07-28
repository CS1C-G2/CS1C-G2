#ifndef CIRCLE_H
#define CIRCLE_H
#include "Shape.h"
class Circle : public Shape
{
public:
    Circle(int id, int x, int y, int radius, QPen* pen, QBrush* brush);
    Circle(int id) : Shape(id) {}
    virtual bool serializeShape(istream& is) override;
    virtual ~Circle() {}
    void draw() override;
    void move(int x, int y) override;
    double area() override;
    double perimeter() override;
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    virtual void internalSerializeShape(ostream& os) override;
    int x;
    int y;
    int radius;
};
#endif // CIRCLE_H
