#ifndef POLYGON_H
#define POLYGON_H
#include "Shape.h"
class Polygon : public Shape, public QGraphicsItem
{
public:
    Polygon(int id, myStd::vector<int> x, myStd::vector<int> y, QPen* pen, QBrush* brush);
    Polygon(int id) : Shape(id) {}
    virtual ~Polygon() {}
    void draw() override;
    virtual bool serializeShape(istream& is) override;

    void move(int x, int y) override;

    double area() override;

    double perimeter() override;

    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

private:
    virtual void internalSerializeShape(ostream& os) override;

    QPen* pen;
    QBrush* brush;
    myStd::vector<int> x;
    myStd::vector<int> y;

};
#endif // POLYGON_H
