#include "circle.h"
Circle::Circle(int id, int x, int y, int radius, QPen* pen, QBrush* brush) :
    Shape(id), x{x}, y{y}, radius{radius} { }
void Circle::draw() {
    update();
}
void Circle::move(int x, int y) {
    this->x = x;
    this->y = y;
    draw();
}
double Circle::area() {
    return pi * pow(radius, 2);
}
double Circle::perimeter() {
    return 2 * pi * radius;
}
QRectF Circle::boundingRect() const {
    return QRectF(x, y, radius * 2, radius * 2);
}
void Circle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(*pen);
    painter->setBrush(*brush);
    painter->drawEllipse(x, y, radius, radius);
}

bool Circle::serializeShape(istream& is)
{
    bool validShape = true;
    // in here read in the shape stuffs from the stream
    IntVecField ivf;
    if (parseIntVectorField(is, "ShapeDimensions", ivf))
    {
        if (ivf.second.size() == 3)
        {
            x = ivf.second[0];
            y = ivf.second[1];
            radius = ivf.second[2];

            pen = serializePen(is);
            brush = serializeBrush(is);
        }
        else
        {
            validShape = false;
        }
    }
    else
    {
        validShape = false;
    }

    return validShape && pen != nullptr && brush != nullptr;
}

void Circle::internalSerializeShape(ostream& os)
{
    serializeStringField(os, "ShapeType", "Circle");
    std::vector<int> dims {x, y, radius};
    serializeIntVectorField(os, "ShapeDimensions", dims);
    serializePen(os);
    serializeBrush(os);
}
