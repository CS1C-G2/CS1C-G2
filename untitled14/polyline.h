#ifndef POLYLINE_H
#define POLYLINE_H
#include "Shape.h"

class Polyline : public Shape
{
public:
    Polyline(int id, myStd::vector<int> x, myStd::vector<int> y, QPen* pen);

    Polyline(int id) : Shape(id) {}
    virtual ~Polyline() {}
    void draw() override;
    virtual bool serializeShape(istream& is) override;

    void move(int x, int y) override;

    double area() override;

    double perimeter() override;

    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    virtual void internalSerializeShape(ostream& os) override;

    myStd::vector<int> x;
    myStd::vector<int> y;

};
#endif // POLYLINE_H
