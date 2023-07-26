#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <utility>
#include <map>
#include <vector>
#include <QFont>
#include "vector_doubles.h"

//using myStd::vector;
using std::istream;
using std::stringstream;
using std::ifstream;
using std::cout;
using std::endl;
using std::map;
using std::streamsize;
using std::string;
using std::numeric_limits;

enum SHAPE_TYPES { LINE, POLYLINE, POLYGON, RECTANGLE, SQUARE, ELLIPSE, CIRCLE, TEXT };

//typedef for std::pairs
typedef std::pair<string, std::vector<int> > IntVecField;
typedef std::pair<string, string> StringField;

/*=======================================================================================
 * STANDALONE FUNCTION - parseStringField, parseIntVectorField
 * =====================================================================================*/

bool parseStringField(istream& is, const string& expectedFieldName, StringField& sf);
bool parseIntVectorField(istream& is, const string& expectedFieldName, IntVecField& ivf);

/*=======================================================================================
 * (TEMPLATED) STANDALONE FUNCTION - parseEnumField
 * =====================================================================================*/

template<typename T>
bool parseEnumField(istream& is, const string& expectedFieldName, const map<string, T>& m, T& e)
{
    StringField sf;
    bool ret = parseStringField(is, expectedFieldName, sf);
    if (!ret)
        return false;

    auto it = m.find(sf.second);
    if(it == m.end())
        return false;

    e = it->second;
    return true;
}

/*=======================================================================================
 * QPEN CLASS
 * =====================================================================================*/

class QPen
{
public:
    QPen(Qt::GlobalColor, int, Qt::PenStyle, Qt::PenCapStyle, Qt::PenJoinStyle) {}
};

/*=======================================================================================
 * QBRUSH CLASS
 * =====================================================================================*/

class QBrush
{
public:
    QBrush(Qt::GlobalColor, Qt::BrushStyle) {}
};

/*=======================================================================================
 * QPOINT CLASS
 * =====================================================================================*/

class QPoint
{
public:
    QPoint(int, int) {}
};

/*=======================================================================================
 * SHAPE CLASS
 * =====================================================================================*/

class Shape
{
public:
    Shape(int id) : shapeID(id), pen(nullptr) {}
    //virtual string getName() = 0;
    virtual ~Shape() { if (pen != nullptr) delete pen; }
    virtual bool serializeShape(istream& is) = 0;
protected:
    QPen* serializePen(istream& is); // allocates a QPen and initializes from data read from the stream
    QBrush* serializeBrush(istream& is);
    QFont* serializeFont(istream& is);

    QPen* pen;
    QBrush* brush;
    QFont* font;
    int shapeID;
};

/*=======================================================================================
 * LINE CLASS
 * =====================================================================================*/

class Line : public Shape
{
public:
    //
    Line(int id) : Shape(id) {}
    virtual bool serializeShape(istream& is) override;
    virtual ~Line() {}
protected:
    int x1, y1, x2, y2;
};

/*=======================================================================================
 * POLYLINE CLASS
 * =====================================================================================*/

class Polyline : public Shape
{
public:
    virtual ~Polyline() {}
    Polyline(int id) : Shape(id) {}
    virtual bool serializeShape(istream& is) override;
protected:
    std::vector<int> points;
};

/*=======================================================================================
 * POLYGON CLASS
 * =====================================================================================*/

class Polygon : public Shape
{
public:
    virtual ~Polygon() {}
    Polygon(int id) : Shape(id) {}
    virtual bool serializeShape(istream& is) override;
protected:
    std::vector<int> points;
};


/*=======================================================================================
 * RECTANGLE CLASS
 * =====================================================================================*/

class Rectangle : public Shape
{
public:
    Rectangle(int id) : Shape(id) {}
    virtual bool serializeShape(istream& is) override;

    virtual ~Rectangle() {}
protected:
    int x, y, w, h;
};

/*=======================================================================================
 * SQUARE CLASS
 * =====================================================================================*/

class Square : public Shape
{
public:
    Square(int id) : Shape(id) {}
    virtual bool serializeShape(istream& is) override;
    virtual ~Square() {}
protected:
    int x, y, w;
};

/*=======================================================================================
 * ELLIPSE CLASS
 * =====================================================================================*/

class Ellipse : public Shape
{
public:
    Ellipse(int id) : Shape(id) {}
    virtual bool serializeShape(istream& is) override;
    virtual ~Ellipse() {}
protected:
    int x, y, w, h;
};

/*=======================================================================================
 * CIRCLE CLASS
 * =====================================================================================*/

class Circle : public Shape
{
public:
    Circle(int id) : Shape(id) {}
    virtual bool serializeShape(istream& is) override;
    virtual ~Circle() {}
protected:
    int x, y, r;
};


/*=======================================================================================
 * TEXT CLASS
 * =====================================================================================*/

class Text : public Shape
{
public:
    Text(int id) : Shape(id) {}
    virtual bool serializeShape(istream& is) override;
protected:
    Qt::AlignmentFlag align;
    Qt::GlobalColor textColor;
    string textStr;
    string textFont;
    int x, y, w, h;
};

/*=======================================================================================
 * SHAPEFACTORY CLASS
 * =====================================================================================*/

class ShapeFactory	//reads in shape type, based on type allocate the correct type of shape.
{
public:
    Shape* createFromStream(istream& is);	//factory method
};

#endif // PARSER_H
