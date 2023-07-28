#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "Shape.h"
class Ellipse : public Shape, public QGraphicsItem
{
public:
    Ellipse(int id, int x, int y, int radius1, int radius2,
            QPen* pen, QBrush* brush);
    Ellipse(int id) : Shape(id) {}
    virtual bool serializeShape(istream& is) override;
    virtual ~Ellipse() {}
    void draw() override;

    void move(int x, int y) override;

    double area() override;

    double perimeter() override;

    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    virtual void internalSerializeShape(ostream& os) override;

    Qt::GlobalColor PenColor;
    QPen* pen;
    QBrush* brush;
    int x;
    int y;
    int radius1;
    int radius2;
};

#endif // ELLIPSE_H
