#include "square.h"
Square::Square(int id, int x, int y, int length, QPen* pen, QBrush* brush) :
    Shape(id, SQUARE), x{x}, y{y}, length{length} { }
void Square::draw() {
    update();
}
void Square::move(int x, int y) {
    this->x = x;
    this->y = y;
    draw();
}
double Square::area() {
    return length * length;
}
double Square::perimeter() {
    return 4 * length;
}
QRectF Square::boundingRect() const {
    return QRectF(x, y, length, length);
}

void Square::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(*pen);
    painter->setBrush(*brush);
    painter->drawRect(x, y, length, length);
}
bool Square::serializeShape(istream& is)
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
            length = ivf.second[2];

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

void Square::internalSerializeShape(ostream& os)
{
    serializeStringField(os, "ShapeType", "Square");
    std::vector<int> dims {x, y, length};
    serializeIntVectorField(os, "ShapeDimensions", dims);
    serializePen(os);
    serializeBrush(os);
}
