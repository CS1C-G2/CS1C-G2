#ifndef SQUARE_H
#define SQUARE_H
#include "Shape.h"
class Square : public Shape
{
public:
    Square(int id, int x, int y, int length, QPen* pen, QBrush* brush);
    Square(int id) : Shape(id) {}
    virtual bool serializeShape(istream& is) override;
    virtual ~Square() {}
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
    int length;
};
#endif // SQUARE_H
