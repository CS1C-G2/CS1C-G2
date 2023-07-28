#include "ellipse.h"
Ellipse::Ellipse(int id, int x, int y, int radius1, int radius2,
                 QPen* pen, QBrush* brush) : Shape(id, ELLIPSE), x{x}, y{y},
    radius1{radius1}, radius2{radius2} { }
void Ellipse::draw() {
    update();
}
void Ellipse::move(int x, int y) {
    this->x = x;
    this->y = y;
    draw();
}
double Ellipse::area() {
    return pi * radius1 * radius2;
}
double Ellipse::perimeter() {
    return  M_PI * (3 * (radius1 + radius2) - sqrt((3 * radius1 + radius2) * (radius1 + 3 * radius2)));
}
QRectF Ellipse::boundingRect() const {
    return QRectF(x, y, radius1 * 2, radius2 * 2);
}
void Ellipse::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(*pen);
    painter->setBrush(*brush);
    painter->drawEllipse(x, y, radius1, radius2);
}

bool Ellipse::serializeShape(istream& is)
{
    bool validShape = true;
    // in here read in the shape stuffs from the stream
    IntVecField ivf;
    if (parseIntVectorField(is, "ShapeDimensions", ivf))
    {
        if (ivf.second.size() == 4)
        {
            x = ivf.second[0];
            y = ivf.second[1];
            radius1 = ivf.second[2];
            radius2 = ivf.second[3];

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

void Ellipse::internalSerializeShape(ostream& os)
{
    serializeStringField(os, "ShapeType", "Ellipse");
    std::vector<int> dims {x, y, radius1, radius2};
    serializeIntVectorField(os, "ShapeDimensions", dims);
    serializePen(os);
    serializeBrush(os);
}
