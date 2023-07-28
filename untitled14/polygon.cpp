#include "polygon.h"
Polygon::Polygon(int id, myStd::vector<int> x, myStd::vector<int> y, QPen* pen, QBrush* brush) :
    Shape(id, POLYGON), x{x}, y{y} { }
void Polygon::draw() {
    update();
}
void Polygon::move(int x, int y) {
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
double Polygon::area() {
    size_t numPoints = x.size();
    for(size_t i = 0; i < x.size(); i++) {
        //Calculate length of sides. Can just copy code from perimeter
    }
    return 0;
}
double Polygon::perimeter() {
    double perim = 0.0;
    for(int i = 0; i < x.size()-1; i++) {
        perim += sqrt(pow(x[i+1] - x[i], 2) + pow(y[i+1] - y[i], 2));
    }
    perim += sqrt(pow(x[0] - x.back(), 2) + pow(y[0] - y.back(), 2));
    return perim;
}
QRectF Polygon::boundingRect() const {
    return QRectF();
}
void Polygon::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    const int SIZE = x.size();
    QPointF points[SIZE];
    for(int i = 0; i < SIZE; i++) {
        points[i] = QPointF(x[i], y[i]);
    }
    painter->setPen(*pen);
    painter->setBrush(*brush);
    painter->drawPolygon(points, 4);
}


bool Polygon::serializeShape(istream& is)
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

void Polygon::internalSerializeShape(ostream& os)
{
    serializeStringField(os, "ShapeType", "Polygon");
    std::vector<int> dims;
    for (int i = 0; i < x.size(); i++)
    {
        dims.push_back(x[i]);
        dims.push_back(y[i]);
    }
    serializeIntVectorField(os, "ShapeDimensions", dims);
    serializePen(os);
    serializeBrush(os);
}
