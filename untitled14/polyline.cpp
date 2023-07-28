#include "polyline.h"
Polyline::Polyline(int id, myStd::vector<int> x, myStd::vector<int> y, QPen* pen) :
    Shape(id, POLYLINE), x{x}, y{y} { }
void Polyline::draw() {
    update();
}
void Polyline::move(int x, int y) {
    int xDiff = this->x[0] - x;
    int yDiff = this->y[0] - y;
    this->x[0] = x;
    this->y[0] = y;
    for(int i = 1; i < this->x.size(); i++) {
        this->x[i] += xDiff;
        this->y[i] += yDiff;
    }
    draw();
}
double Polyline::area() {
    return 0;
}
double Polyline::perimeter() {
    return 0;
}
QRectF Polyline::boundingRect() const {
    return QRectF();
}
void Polyline::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(*pen);
    const int SIZE = x.size();
    QPointF points[SIZE];
    for(int i = 0; i < SIZE; i++) {
        points[i] = QPointF(x[i], y[i]);
    }
    painter->drawPolyline(points, SIZE);
}

bool Polyline::serializeShape(istream& is)
{
    bool validShape = true;
    // in here read in the shape stuffs from the stream
    IntVecField ivf;
    if (parseIntVectorField(is, "ShapeDimensions", ivf))
    {
        if (ivf.second.size() >= 4 && ivf.second.size() % 2 == 0)
        {
            for (int i = 0; i < ivf.second.size(); i += 2)
            {
                x.push_back(ivf.second[i]);
                y.push_back(ivf.second[i + 1]);
            }

            pen = serializePen(is);
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

    return validShape && pen != nullptr;
}

void Polyline::internalSerializeShape(ostream& os)
{
    serializeStringField(os, "ShapeType", "Polyline");
    std::vector<int> dims;
    for (int i = 0; i < x.size(); i++)
    {
        dims.push_back(x[i]);
        dims.push_back(y[i]);
    }
    serializeIntVectorField(os, "ShapeDimensions", dims);
    serializePen(os);
}
