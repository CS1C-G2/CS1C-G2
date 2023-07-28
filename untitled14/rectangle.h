#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Shape.h"
class Rectangle : public Shape
{
public:
    Rectangle(int id, int x, int y, int length, int width, QPen* pen, QBrush* brush);

    Rectangle(int id) : Shape(id) {}
    virtual ~Rectangle() {}
    void draw() override;
    virtual bool serializeShape(istream& is) override;

    void move(int x, int y) override;

    double area() override;

    double perimeter() override;

    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
protected:
    virtual void internalSerializeShape(ostream& os) override;

    int x;
    int y;
    int length;
    int width;
};
#endif // RECTANGLE_H
