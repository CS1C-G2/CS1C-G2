#ifndef SHAPE_H
#define SHAPE_H
//#include "mainwindow.h"
#include "qgraphicsitem.h"
#include <QMainWindow>
#include <QMainWindow>
#include <QPainter>
#include <QPaintEvent>
#include <QColor>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <vector>
#include <cmath>
#include <QFont>
#include <iostream>
#include "vector.cpp"

using namespace std;
using myStd::vector;

//typedef for std::pairs
typedef std::pair<string, std::vector<int> > IntVecField;
typedef std::pair<string, string> StringField;

/*=======================================================================================
 * STANDALONE FUNCTION - parseStringField, parseIntVectorField
 * =====================================================================================*/

bool parseStringField(istream& is, const string& expectedFieldName, StringField& sf);
bool parseIntVectorField(istream& is, const string& expectedFieldName, IntVecField& ivf);
void serializeIntVectorField(ostream& os, const string& fieldName, const std::vector<int>& v);
void serializeStringField(ostream& os, const string& fieldName, const string& fieldValue);

/*=======================================================================================
 * (TEMPLATED) STANDALONE FUNCTIONS - parseEnumField, serializeEnumField
 * =====================================================================================*/

template<typename T>
bool parseEnumField(istream& is, const string& expectedFieldName, const map<string, T>& m, T& e)
{
    StringField sf;
    bool ret = parseStringField(is, expectedFieldName, sf);
    if (!ret)
        return false;

    auto it = m.find(sf.second);
    if (it == m.end())
        return false;

    e = it->second;
    return true;
}

template <typename T>
void serializeEnumField(ostream& os, const string& fieldname, const map<T, string>& m, T e)
{
    os << fieldname << ": " << m.find(e)->second << endl;
}

/*=======================================================================================
 * SHAPE CLASS
 * =====================================================================================*/

const double pi = 3.14;
enum SHAPE_TYPES { LINE, POLYLINE, POLYGON, RECTANGLE, SQUARE, ELLIPSE, CIRCLE, TEXT };

class Shape : public QGraphicsItem
{
public:
    Shape() {id = 0;}
    Shape(int id) : id(id), pen(nullptr), brush(nullptr), font(nullptr) {}
    Shape(int id, SHAPE_TYPES type): type{type}, id{id} {}

    virtual ~Shape()
    {
        delete pen;
        delete brush;
        delete font;

        this->pen = nullptr;
        this->brush = nullptr;
        this->font = nullptr;
    }
    virtual bool serializeShape(istream& is) = 0;
    void serializeShape(ostream& os);
    virtual void draw() = 0;

    virtual void move(int x, int y) = 0;

    virtual double area() = 0;

    virtual double perimeter() = 0;

    int getId() const {return id;}
    void SetShapeType(SHAPE_TYPES t) { type = t;  }
    SHAPE_TYPES getType() const {return type;}

protected:
    virtual void internalSerializeShape(ostream& os) = 0;
    QPen* serializePen(istream& is);
    QBrush* serializeBrush(istream& is);
    QFont* serializeFont(istream& is);
    void serializePen(ostream& os);
    void serializeBrush(ostream& os);
    void serializeFont(ostream& os);

    int id;
    SHAPE_TYPES type;
    QPen* pen;
    Qt::GlobalColor penColor;
    QBrush* brush;
    Qt::GlobalColor brushColor;
    QFont* font;


    static map<string, Qt::GlobalColor> colorMap;
    static map<string, Qt::PenStyle> penStyleMap;
    static map<string, Qt::PenCapStyle> penCapStyleMap;
    static map<string, Qt::PenJoinStyle> penJoinStyleMap;
    static map<string, Qt::BrushStyle> brushStyleMap;
    static map<string, Qt::AlignmentFlag> alignmentFlagMap;
    static map<string, QFont::Style> fontStyleMap;
    static map<string, QFont::Weight> fontWeightMap;

    static map<Qt::GlobalColor, string> colorSerializeMap;
    static map<Qt::PenStyle, string> penStyleSerializeMap;
    static map<Qt::PenCapStyle, string> penCapStyleSerializeMap;
    static map<Qt::PenJoinStyle, string> penJoinStyleSerializeMap;
    static map<Qt::BrushStyle, string> brushStyleSerializeMap;
    static map<Qt::AlignmentFlag, string> alignmentFlagSerializeMap;
    static map<QFont::Style, string> fontStyleSerializeMap;
    static map<QFont::Weight, string> fontWeightSerializeMap;

};

#endif // SHAPE_H
