#include "rectangle.h"
Rectangle::Rectangle(int id, int x, int y, int length, int width, QPen* pen, QBrush* brush) :
    Shape(id, RECTANGLE), x{x}, y{y}, length{length}, width{width} { }
void Rectangle::draw() {
    update();
}
void Rectangle::move(int x, int y) {
    this->x = x;
    this->y = y;
    draw();
}
double Rectangle::area() {
    return length * width;
}
double Rectangle::perimeter() {
    return (length * 2) + (width * 2);
}
QRectF Rectangle::boundingRect() const {
    return QRectF(x, y, width, length);
}
void Rectangle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(*pen);
    painter->setBrush(*brush);
    painter->drawRect(x, y, length, width);
}

bool Rectangle::serializeShape(istream& is)
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
            length = ivf.second[2];
            width = ivf.second[3];

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

void Rectangle::internalSerializeShape(ostream& os)
{
    serializeStringField(os, "ShapeType", "Rectangle");
    std::vector<int> dims {x, y, length, width};
    serializeIntVectorField(os, "ShapeDimensions", dims);
    serializePen(os);
    serializeBrush(os);
}
