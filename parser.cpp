//Parsing

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

map<string, Qt::GlobalColor> colorMap
{
    {"black", Qt::black},
    {"white", Qt::white},
    {"darkGray", Qt::darkGray},
    {"gray", Qt::gray},
    {"lightGray", Qt::lightGray},
    {"red", Qt::red},
    {"green", Qt::green},
    {"blue", Qt::blue},
    {"cyan", Qt::cyan},
    {"magenta", Qt::magenta},
    {"yellow", Qt::yellow},
    {"darkRed", Qt::darkRed},
    {"darkGreen", Qt::darkGreen},
    {"darkBlue", Qt::darkBlue},
    {"darkCyan", Qt::darkCyan},
    {"darkMagenta", Qt::darkMagenta},
    {"darkYellow", Qt::darkYellow},
    {"transparent", Qt::transparent},
};

map<string, Qt::PenStyle> penStyleMap
{
    {"NoPen", Qt::NoPen},
    {"SolidLine", Qt::SolidLine},
    {"DashLine", Qt::DashLine},
    {"DotLine", Qt::DotLine},
    {"DashDotLine", Qt::DashDotLine},
    {"DashDotDotLine", Qt::DashDotDotLine},
};

map<string, Qt::PenCapStyle> penCapStyleMap
{
    {"FlatCap", Qt::FlatCap},
    {"SquareCap", Qt::SquareCap},
    {"RoundCap", Qt::RoundCap},
};

map<string, Qt::PenJoinStyle> penJoinStyleMap
{
    {"MiterJoin", Qt::MiterJoin},
    {"BevelJoin", Qt::BevelJoin},
    {"RoundJoin", Qt::RoundJoin},
    {"SvgMiterJoin", Qt::SvgMiterJoin},
};

map<string, Qt::BrushStyle> brushStyleMap
{
    {"NoBrush", Qt::NoBrush},
    {"SolidPattern", Qt::SolidPattern},
    {"Dense1Pattern", Qt::Dense1Pattern},
    {"Dense2Pattern", Qt::Dense2Pattern},
    {"Dense3Pattern", Qt::Dense3Pattern},
    {"Dense4Pattern", Qt::Dense4Pattern},
    {"Dense5Pattern", Qt::Dense5Pattern},
    {"Dense6Pattern", Qt::Dense6Pattern},
    {"Dense7Pattern", Qt::Dense7Pattern},
    {"HorPattern", Qt::HorPattern},
    {"VerPattern", Qt::VerPattern},
    {"CrossPattern", Qt::CrossPattern},
    {"BDiagPattern", Qt::BDiagPattern},
    {"FDiagPattern", Qt::FDiagPattern},
    {"DiagCrossPattern", Qt::DiagCrossPattern},
    {"LinearGradientPattern", Qt::LinearGradientPattern},
    {"ConicalGradientPattern", Qt::ConicalGradientPattern},
    {"RadialGradientPattern", Qt::RadialGradientPattern},
    {"TexturePattern", Qt::TexturePattern},
};

map<string, Qt::AlignmentFlag> alignmentFlagMap
{
    {"AlignCenter", Qt::AlignCenter},
    {"AlignLeft", Qt::AlignLeft},
    {"AlignRight", Qt::AlignRight},
    {"AlignJustify", Qt::AlignJustify},
    {"AlignTop", Qt::AlignTop},
    {"AlignBottom", Qt::AlignBottom},
    {"AlignVCenter", Qt::AlignVCenter},
    {"AlignBaseLine", Qt::AlignBaseline},
};

map<string, QFont::Style> fontStyleMap	//double ::?
{
    {"StyleNormal", QFont::StyleNormal},
    {"StyleItalic", QFont::StyleItalic},
    {"StyleOblique", QFont::StyleOblique},
};

map<string, QFont::Weight> fontWeightMap
{
    {"Thin", QFont::Thin},
    {"ExtraLight", QFont::ExtraLight},
    {"Light", QFont::Light},
    {"Normal", QFont::Normal},
    {"Medium", QFont::Medium},
    {"DemiBold", QFont::DemiBold},
    {"Bold", QFont::Bold},
    {"ExtraBold", QFont::ExtraBold},
    {"Black", QFont::Black},
};


class QPen
{
public:
    QPen(Qt::GlobalColor, int, Qt::PenStyle, Qt::PenCapStyle, Qt::PenJoinStyle) {}
};

class QBrush
{
public:
    QBrush(Qt::GlobalColor, Qt::BrushStyle) {}
};

class QPoint
{
public:
    QPoint(int, int) {}
};

// FROM HERE DOWN IS YOUR CODE, ALL THE Q WHATEVER CLASSES ARE QT AND CAN BE INCLUDED

enum SHAPE_TYPES { LINE, POLYLINE, POLYGON, RECTANGLE, SQUARE, ELLIPSE, CIRCLE, TEXT };

typedef std::pair<string, std::vector<int> > IntVecField;
typedef std::pair<string, string> StringField;

bool parseIntVectorField(istream& is, const string& expectedFieldName, IntVecField& ivf)
{

    string line;

    getline(is, line);	//gets whole line
    auto pos=line.find(':');	//if pos = npos, no find : bulletproof needed TODO
    ivf.first = line.substr(0, pos);	//gives just feildName
    stringstream fieldstr(line.substr(pos+1, line.size()));	//make a stream, but have the thing youre streaming from be this string


    while(!fieldstr.eof())	//bulletproof to make sure it only reads ints TODO
    {
        int x;
        fieldstr >> x;
        fieldstr.ignore(',');
        ivf.second.push_back(x);
    }

    if (expectedFieldName.compare(ivf.first) != 0)
    {
        return false;
    }


    return true;	//returns a struct of the name and the numbers following
}

bool parseStringField(istream& is, const string& expectedFieldName, StringField& sf)
{
    string line;

    getline(is, line);  //gets whole line
    auto pos=line.find(':');    //if pos = npos, no find : bulletproof needed TODO
    sf.first = line.substr(0, pos);
    sf.second = line.substr(pos+1, line.size());

    if (expectedFieldName.compare(sf.first) != 0)
    {
        return false;
    }

    return true;
}

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

class Shape
{
public:
    Shape(int id) : shapeID(id), pen(nullptr) {}
    //virtual string getName() = 0;
    virtual ~Shape() { if (pen != nullptr) delete pen; }
    virtual bool serializeShape(istream& is) = 0;
protected:
    QPen* serializePen(istream& is) // allocates a QPen and initializes from data read from the stream
    {
         int width;
        IntVecField ivf;
        StringField sf;

        Qt::GlobalColor penColor = Qt::black;
        Qt::PenStyle penStyle = Qt::SolidLine;
        Qt::PenCapStyle penCapStyle = Qt::SquareCap;
        Qt::PenJoinStyle penJoinStyle = Qt::BevelJoin;

        if(!parseEnumField<Qt::GlobalColor>(is, "PenColor", colorMap, penColor))
        {
            return nullptr;
        }

        if(parseIntVectorField(is, "PenWidth", ivf))
        {
            if(ivf.second.size() == 1)
            {
                width = ivf.second[0];
            }
            else
            {
                return nullptr;
            }
        }

        if(!parseEnumField<Qt::PenStyle>(is, "PenStyle", penStyleMap, penStyle))
        {
            return nullptr;
        }

        if(!parseEnumField<Qt::PenCapStyle>(is, "PenCapStyle", penCapStyleMap, penCapStyle))
        {
            return nullptr;
        }

        if(!parseEnumField<Qt::PenJoinStyle>(is, "PenJoinStyle", penJoinStyleMap, penJoinStyle))
        {
            return nullptr;
        }

        return new QPen(penColor, width, penStyle, penCapStyle, penJoinStyle);
    }

    QBrush* serializeBrush(istream& is) // allocates a QBrush and initializes from data read from the stream
    {
        string color;
        string style;
        StringField sf;

        Qt::GlobalColor brushColor = Qt::black;
        Qt::BrushStyle brushStyle = Qt::SolidPattern;

        if(!parseEnumField<Qt::GlobalColor>(is, "BrushColor", colorMap, brushColor))
        {
            return nullptr;
        }

        if(!parseEnumField<Qt::BrushStyle>(is, "BrushStyle", brushStyleMap, brushStyle))
        {
            return nullptr;
        }

        return new QBrush(brushColor, brushStyle);
    }


        QFont* serializeFont(istream& is)
        {
            IntVecField ivf;
            int textPointSize;

            StringField sf;
            string textFontFamily;

            QFont::Weight weight;
            QFont::Style style;

            if(parseIntVectorField(is, "textPointSize", ivf))
            {
                if(ivf.second.size() == 1)
                {
                    textPointSize = ivf.second[0];
                }
                else
                {
                    return nullptr;
                }
            }
            else
            {
                return nullptr;
            }


            if(parseStringField(is, "TextFontFamily", sf))
            {
                textFontFamily = sf.second;
            }
            else
            {
                return nullptr;
            }


            if(!parseEnumField<QFont::Style>(is, "TextFontStyle", fontStyleMap, style))
            {
                return nullptr;
            }

            if(!parseEnumField<QFont::Weight>(is, "TextFontWeight", fontWeightMap, weight))
            {
                return nullptr;
            }
            QFont* f = new QFont(QString(textFontFamily.c_str()), textPointSize);
            f->setStyle(style);
            f->setWeight(weight);
            return f;
        }


        QPen* pen;
        QBrush* brush;
        QFont* font;
        int shapeID;
    };

    class Line : public Shape
    {
    public:
        //
        Line(int id) : Shape(id) {}
        virtual bool serializeShape(istream& is) override
        {
            bool validShape = true;
            // in here read in the shape stuffs from the stream
            IntVecField ivf;

            if(parseIntVectorField(is, "ShapeDimensions", ivf))
            {
                if(ivf.second.size() == 4)
                {
                    x1 = ivf.second[0];
                    y1 = ivf.second[1];
                    x2 = ivf.second[2];
                    y2 = ivf.second[3];
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


            pen = serializePen(is);
            return validShape && pen != nullptr;
        }

        virtual ~Line() {}
    protected:
        int x1, y1, x2, y2;


    };

class Polyline : public Shape
{
public:
    virtual ~Polyline() {}
    Polyline(int id) : Shape(id) {}
    virtual bool serializeShape(istream& is) override
    {
        bool validShape = true;
        // in here read in the shape stuffs from the stream
        IntVecField ivf;
        if(parseIntVectorField(is, "ShapeDimensions", ivf))
        {
            if(ivf.second.size() >= 4 && ivf.second.size() % 2 == 0)
            {
                points = ivf.second;
            }
            else
            {
                validShape = false;
            }

            pen = serializePen(is);
            return validShape && pen != nullptr;
        }
    }
protected:
    std::vector<int> points;
};

class Polygon : public Shape
{
public:
    virtual ~Polygon() {}
    Polygon(int id) : Shape(id) {}
    virtual bool serializeShape(istream& is) override
    {
        bool validShape = true;
        // in here read in the shape stuffs from the stream
        IntVecField ivf;
        if(parseIntVectorField(is, "ShapeDimensions", ivf))
        {
            if(ivf.second.size() >= 4 && ivf.second.size() % 2 == 0)
            {
                points = ivf.second;
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

        pen = serializePen(is);
        brush = serializeBrush(is);
        return validShape && pen != nullptr && brush != nullptr;
    }
protected:
    std::vector<int> points;
};

class Rectangle : public Shape
{
public:
    Rectangle(int id) : Shape(id) {}
    virtual bool serializeShape(istream& is) override
    {
        bool validShape = true;
        // in here read in the shape stuffs from the stream
        IntVecField ivf;
        if(parseIntVectorField(is, "ShapeDimensions", ivf))
        {
            if(ivf.second.size() == 4)
            {
                x = ivf.second[0];
                y = ivf.second[1];
                w = ivf.second[2];
                h = ivf.second[3];
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

        pen = serializePen(is);
        brush = serializeBrush(is);
        return validShape && pen != nullptr && brush != nullptr;
    }

    virtual ~Rectangle() {}
protected:
    int x, y, w, h;
};

class Square : public Shape
{
public:
    Square(int id) : Shape(id) {}
    virtual bool serializeShape(istream& is) override
    {
        bool validShape = true;
        // in here read in the shape stuffs from the stream
        IntVecField ivf;
        if(parseIntVectorField(is, "ShapeDimensions", ivf))
        {
            if(ivf.second.size() == 3)
            {
                x = ivf.second[0];
                y = ivf.second[1];
                w = ivf.second[2];
            }
            else
            {
                validShape = false;
            }

            pen = serializePen(is);
            brush = serializeBrush(is);
            return validShape && pen != nullptr && brush != nullptr;
        }
    }
    virtual ~Square() {}
protected:
    int x, y, w;
};

class Ellipse : public Shape
{
public:
    Ellipse(int id) : Shape(id) {}
    virtual bool serializeShape(istream& is) override
    {
        bool validShape = true;
        // in here read in the shape stuffs from the stream
        IntVecField ivf;
        if(parseIntVectorField(is, "ShapeDimensions", ivf))
        {
            if(ivf.second.size() == 4)
            {
                x = ivf.second[0];
                y = ivf.second[1];
                w = ivf.second[2];
                h = ivf.second[3];
            }
            else
            {
                validShape = false;
            }

            pen = serializePen(is);
            brush = serializeBrush(is);
            return validShape && pen != nullptr && brush != nullptr;
        }
    }
    virtual ~Ellipse() {}
protected:
    int x, y, w, h;
};

class Circle : public Shape
{
public:
    Circle(int id) : Shape(id) {}
    virtual bool serializeShape(istream& is) override
    {
        bool validShape = true;
        // in here read in the shape stuffs from the stream
        IntVecField ivf;
        if(parseIntVectorField(is, "ShapeDimensions", ivf))
        {
            if(ivf.second.size() == 3)
            {
                x = ivf.second[0];
                y = ivf.second[1];
                r = ivf.second[2];
            }
            else
            {
                validShape = false;
            }

            pen = serializePen(is);
            brush = serializeBrush(is);
            return validShape && pen != nullptr && brush != nullptr;
        }
    }
    virtual ~Circle() {}
protected:
    int x, y, r;
};

class Text : public Shape
{
public:
    Text(int id) : Shape(id) {}
    virtual bool serializeShape(istream& is) override
    {
        bool validShape = true;
        // in here read in the shape stuffs from the stream
        IntVecField ivf;
        if(parseIntVectorField(is, "ShapeDimensions", ivf))
        {
            if(ivf.second.size() == 4)
            {
                x = ivf.second[0];
                y = ivf.second[1];
                w = ivf.second[2];
                h = ivf.second[3];
            }
            else
            {
                validShape = false;
            }

            StringField sf;
            if(parseStringField(is, "TextString", sf))
            {
                textStr = sf.second;
            }
            else
            {
                validShape = false;
            }

            if(!parseEnumField<Qt::GlobalColor>(is, "TextColor", colorMap, textColor))
            {
                validShape = false;
            }

            if(!parseEnumField<Qt::AlignmentFlag>(is, "TextAlignment", alignmentFlagMap, align))
            {
                validShape = false;
            }

            font = serializeFont(is);	//implement please
            return validShape;
        }
    }
protected:
    Qt::AlignmentFlag align;
    Qt::GlobalColor textColor;
    string textStr;
    string textFont;
    int x, y, w, h;
};

class ShapeFactory	//reads in shape type, based on type allocate the correct type of shape.
{
public:
        Shape* createFromStream(istream& is)	//factory method
        {
            SHAPE_TYPES t;
            Shape* s = nullptr;

            int shapeID;

            IntVecField shapeIdFeild;
            if(parseIntVectorField(is, "ShapeId", shapeIdFeild))
            {
                shapeID = shapeIdFeild.second[0];	//TODO: later make sure size is 1
            }

            StringField shapeType;
            if(parseStringField(is, "ShapeType", shapeType))
            {
                if(shapeType.second.compare("Line") == 0)
                {
                    s = new Line(shapeID);
                }
                else if (shapeType.second.compare("Polyline") == 0)
                {
                    s = new Polyline(shapeID);
                }
                else if (shapeType.second.compare("Polygon") == 0)
                {
                    s = new Polygon(shapeID);
                }
                else if (shapeType.second.compare("Rectangle") == 0)
                {
                    s = new Rectangle(shapeID);
                }
                else if (shapeType.second.compare("Square") == 0)
                {
                    s = new Square(shapeID);
                }
                else if (shapeType.second.compare("Ellipse") == 0)
                {
                    s = new Ellipse(shapeID);
                }
                else if(shapeType.second.compare("Circle") == 0)
                {
                    s = new Circle(shapeID);
                }
                else if (shapeType.second.compare("Text") == 0)
                {
                    s = new Text(shapeID);
                }

                if(!s->serializeShape(is))
                {
                    delete s;
                    return nullptr;
                }
            }
            else
            {
                return nullptr;
            }
            return s;
        }
};

#if 0
vector<Shape*> parse(string fileName);

int main()
{
    vector<Shape*> shapes = parse("shapes copy.txt");

    for (Shape* shape : shapes)
    {
        delete shape;
    }

    return 0;
}

vector<Shape*> parse(string fileName)
{
    ifstream inFile;
    ShapeFactory f;

    inFile.open(fileName);

    vector<Shape*> shapes;

    while(!inFile.eof())
    {
        Shape* s = f.createFromStream(inFile);
        if(s != nullptr)	//safe to keep reading bc factory function will only create a shape when it finds a valid shapeid.
        {
            shapes.push_back(s);
        }

    }



    inFile.close();

    return shapes;
}
#endif
