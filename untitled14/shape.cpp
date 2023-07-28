//shape.cpp

#include "shape.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <utility>
#include <map>
#include <vector>
#include <QFont>
#include "shape.h"

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

//Maps string to enum
/*===============================================================================*/
map<string, Qt::GlobalColor> Shape::colorMap
{
    {"black", Qt::black},
    { "white", Qt::white },
    { "darkGray", Qt::darkGray },
    { "gray", Qt::gray },
    { "lightGray", Qt::lightGray },
    { "red", Qt::red },
    { "green", Qt::green },
    { "blue", Qt::blue },
    { "cyan", Qt::cyan },
    { "magenta", Qt::magenta },
    { "yellow", Qt::yellow },
    { "darkRed", Qt::darkRed },
    { "darkGreen", Qt::darkGreen },
    { "darkBlue", Qt::darkBlue },
    { "darkCyan", Qt::darkCyan },
    { "darkMagenta", Qt::darkMagenta },
    { "darkYellow", Qt::darkYellow },
    { "transparent", Qt::transparent },
};

map<string, Qt::PenStyle> Shape::penStyleMap
{
    {"NoPen", Qt::NoPen},
    { "SolidLine", Qt::SolidLine },
    { "DashLine", Qt::DashLine },
    { "DotLine", Qt::DotLine },
    { "DashDotLine", Qt::DashDotLine },
    { "DashDotDotLine", Qt::DashDotDotLine },
};

map<string, Qt::PenCapStyle> Shape::penCapStyleMap
{
    {"FlatCap", Qt::FlatCap},
    { "SquareCap", Qt::SquareCap },
    { "RoundCap", Qt::RoundCap },
};

map<string, Qt::PenJoinStyle> Shape::penJoinStyleMap
{
    {"MiterJoin", Qt::MiterJoin},
    { "BevelJoin", Qt::BevelJoin },
    { "RoundJoin", Qt::RoundJoin },
    { "SvgMiterJoin", Qt::SvgMiterJoin },
};

map<string, Qt::BrushStyle> Shape::brushStyleMap
{
    {"NoBrush", Qt::NoBrush},
    { "SolidPattern", Qt::SolidPattern },
    { "Dense1Pattern", Qt::Dense1Pattern },
    { "Dense2Pattern", Qt::Dense2Pattern },
    { "Dense3Pattern", Qt::Dense3Pattern },
    { "Dense4Pattern", Qt::Dense4Pattern },
    { "Dense5Pattern", Qt::Dense5Pattern },
    { "Dense6Pattern", Qt::Dense6Pattern },
    { "Dense7Pattern", Qt::Dense7Pattern },
    { "HorPattern", Qt::HorPattern },
    { "VerPattern", Qt::VerPattern },
    { "CrossPattern", Qt::CrossPattern },
    { "BDiagPattern", Qt::BDiagPattern },
    { "FDiagPattern", Qt::FDiagPattern },
    { "DiagCrossPattern", Qt::DiagCrossPattern },
    { "LinearGradientPattern", Qt::LinearGradientPattern },
    { "ConicalGradientPattern", Qt::ConicalGradientPattern },
    { "RadialGradientPattern", Qt::RadialGradientPattern },
    { "TexturePattern", Qt::TexturePattern },
};

map<string, Qt::AlignmentFlag> Shape::alignmentFlagMap
{
    {"AlignCenter", Qt::AlignCenter},
    { "AlignLeft", Qt::AlignLeft },
    { "AlignRight", Qt::AlignRight },
    { "AlignJustify", Qt::AlignJustify },
    { "AlignTop", Qt::AlignTop },
    { "AlignBottom", Qt::AlignBottom },
    { "AlignVCenter", Qt::AlignVCenter },
    { "AlignBaseLine", Qt::AlignBaseline },
};

map<string, QFont::Style> Shape::fontStyleMap	//double ::?
{
    {"StyleNormal", QFont::StyleNormal},
    { "StyleItalic", QFont::StyleItalic },
    { "StyleOblique", QFont::StyleOblique },
};

map<string, QFont::Weight> Shape::fontWeightMap
{
    {"Thin", QFont::Thin},
    { "ExtraLight", QFont::ExtraLight },
    { "Light", QFont::Light },
    { "Normal", QFont::Normal },
    { "Medium", QFont::Medium },
    { "DemiBold", QFont::DemiBold },
    { "Bold", QFont::Bold },
    { "ExtraBold", QFont::ExtraBold },
    { "Black", QFont::Black },
};

map<Qt::GlobalColor, string> Shape::colorSerializeMap
{
    {Qt::black, "black"},
    { Qt::white, "white" },
    { Qt::darkGray, "darkGray" },
    { Qt::gray, "gray" },
    { Qt::lightGray, "lightGray" },
    { Qt::red, "red" },
    { Qt::green, "green" },
    { Qt::blue, "blue" },
    { Qt::cyan, "cyan" },
    { Qt::magenta, "magenta" },
    { Qt::yellow, "yellow" },
    { Qt::darkRed, "darkRed" },
    { Qt::darkGreen, "darkGreen" },
    { Qt::darkBlue, "darkBlue" },
    { Qt::darkCyan, "darkCyan" },
    { Qt::darkMagenta, "darkMagenta" },
    { Qt::darkYellow, "darkYellow" },
    { Qt::transparent, "transparent" },
};

map<Qt::PenStyle, string> Shape::penStyleSerializeMap
{
    {Qt::NoPen, "NoPen"},
    { Qt::SolidLine, "SolidLine" },
    { Qt::DashLine, "DashLine" },
    { Qt::DotLine, "DotLine" },
    { Qt::DashDotLine, "DashDotLine" },
    { Qt::DashDotDotLine, "DashDotDotLine" },
};

map<Qt::PenCapStyle, string> Shape::penCapStyleSerializeMap
{
    {Qt::FlatCap, "FlatCap"},
    { Qt::SquareCap, "SquareCap" },
    { Qt::RoundCap, "RoundCap" },
};

map<Qt::PenJoinStyle, string> Shape::penJoinStyleSerializeMap
{
    {Qt::MiterJoin, "MiterJoin"},
    { Qt::BevelJoin, "BevelJoin" },
    { Qt::RoundJoin, "RoundJoin" },
    { Qt::SvgMiterJoin, "SvgMiterJoin" },
};

map<Qt::BrushStyle, string> Shape::brushStyleSerializeMap
{
    {Qt::NoBrush, "NoBrush"},
    { Qt::SolidPattern, "SolidPattern" },
    { Qt::Dense1Pattern, "Dense1Pattern" },
    { Qt::Dense2Pattern, "Dense2Pattern" },
    { Qt::Dense3Pattern, "Dense3Pattern" },
    { Qt::Dense4Pattern, "Dense4Pattern" },
    { Qt::Dense5Pattern, "Dense5Pattern" },
    { Qt::Dense6Pattern, "Dense6Pattern" },
    { Qt::Dense7Pattern, "Dense7Pattern" },
    { Qt::HorPattern, "HorPattern" },
    { Qt::VerPattern, "VerPattern" },
    { Qt::CrossPattern, "CrossPattern" },
    { Qt::BDiagPattern, "BDiagPattern" },
    { Qt::FDiagPattern, "FDiagPattern" },
    { Qt::DiagCrossPattern, "DiagCrossPattern" },
    { Qt::LinearGradientPattern, "LinearGradientPattern" },
    { Qt::ConicalGradientPattern, "ConicalGradientPattern" },
    { Qt::RadialGradientPattern, "RadialGradientPattern" },
    { Qt::TexturePattern, "TexturePattern" },
};

map<Qt::AlignmentFlag, string> Shape::alignmentFlagSerializeMap
{
    {Qt::AlignCenter, "AlignCenter"},
    { Qt::AlignLeft, "AlignLeft" },
    { Qt::AlignRight, "AlignRight" },
    { Qt::AlignJustify, "AlignJustify" },
    { Qt::AlignTop, "AlignTop" },
    { Qt::AlignBottom, "AlignBottom" },
    { Qt::AlignVCenter, "AlignVCenter" },
    { Qt::AlignBaseline, "AlignBaseLine" },
};

map<QFont::Style, string> Shape::fontStyleSerializeMap
{
    {QFont::StyleNormal, "StyleNormal"},
    { QFont::StyleItalic, "StyleItalic" },
    { QFont::StyleOblique, "StyleOblique" },
};

map<QFont::Weight, string> Shape::fontWeightSerializeMap
{
    {QFont::Thin, "Thin"},
    { QFont::ExtraLight, "ExtraLight" },
    { QFont::Light, "Light" },
    { QFont::Normal, "Normal" },
    { QFont::Medium, "Medium" },
    { QFont::DemiBold, "DemiBold" },
    { QFont::Bold, "Bold" },
    { QFont::ExtraBold, "ExtraBold" },
    { QFont::Black, "Black" },
};

/*=================================================================================*/

//standalone function
bool parseIntVectorField(istream& is, const string& expectedFieldName, IntVecField& ivf)
{

    string line;

    getline(is, line);	//gets whole line
    auto pos = line.find(':');	//if pos = npos, no find : bulletproof needed TODO
    ivf.first = line.substr(0, pos);	//gives just feildName
    stringstream fieldstr(line.substr(pos + 1, line.size()));	//make a stream, but have the thing youre streaming from be this string


    while (!fieldstr.eof())	//bulletproof to make sure it only reads ints TODO
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

//standalone function
bool parseStringField(istream& is, const string& expectedFieldName, StringField& sf)
{
    string line;

    getline(is, line);  //gets whole line
    auto pos = line.find(':');    //if pos = npos, no find : bulletproof needed TODO
    sf.first = line.substr(0, pos);
    sf.second = line.substr(pos + 1, line.size());

    if (expectedFieldName.compare(sf.first) != 0)
    {
        return false;
    }

    return true;
}

void serializeIntVectorField(ostream& os, const string& fieldName, const vector<int>& v)
{
    os << fieldName << ": ";
    for (int i : v)
    {
        os << i << " ";
    }
    os << endl;
}

void serializeStringField(ostream& os, const string& fieldName, const string& fieldValue)
{
    os << fieldName << ": " << fieldValue << endl;
}

void Shape::serializeShape(ostream& os)
{
    vector<int> id = { this->id };
    serializeIntVectorField(os, "ShapeId", id);
    internalSerializeShape(os);
    os << endl;
}

QPen* Shape::serializePen(istream& is) // allocates a QPen and initializes from data read from the stream
{
    int width;
    IntVecField ivf;
    StringField sf;

    Qt::GlobalColor penColor = Qt::black;
    Qt::PenStyle penStyle = Qt::SolidLine;
    Qt::PenCapStyle penCapStyle = Qt::SquareCap;
    Qt::PenJoinStyle penJoinStyle = Qt::BevelJoin;

    if (!parseEnumField<Qt::GlobalColor>(is, "PenColor", colorMap, penColor))
    {
        return nullptr;
    }

    if (parseIntVectorField(is, "PenWidth", ivf))
    {
        if (ivf.second.size() == 1)
        {
            width = ivf.second[0];
        }
        else
        {
            return nullptr;
        }
    }

    if (!parseEnumField<Qt::PenStyle>(is, "PenStyle", penStyleMap, penStyle))
    {
        return nullptr;
    }

    if (!parseEnumField<Qt::PenCapStyle>(is, "PenCapStyle", penCapStyleMap, penCapStyle))
    {
        return nullptr;
    }

    if (!parseEnumField<Qt::PenJoinStyle>(is, "PenJoinStyle", penJoinStyleMap, penJoinStyle))
    {
        return nullptr;
    }

    return new QPen(penColor, width, penStyle, penCapStyle, penJoinStyle);
}

QBrush* Shape::serializeBrush(istream& is) // allocates a QBrush and initializes from data read from the stream
{
    string color;
    string style;
    StringField sf;

    Qt::GlobalColor brushColor = Qt::black;
    Qt::BrushStyle brushStyle = Qt::SolidPattern;

    if (!parseEnumField<Qt::GlobalColor>(is, "BrushColor", colorMap, brushColor))
    {
        return nullptr;
    }

    if (!parseEnumField<Qt::BrushStyle>(is, "BrushStyle", brushStyleMap, brushStyle))
    {
        return nullptr;
    }

    return new QBrush(brushColor, brushStyle);
}


QFont* Shape::serializeFont(istream& is)
{
    IntVecField ivf;
    int textPointSize;

    StringField sf;
    string textFontFamily;

    QFont::Weight weight;
    QFont::Style style;

    if (parseIntVectorField(is, "textPointSize", ivf))
    {
        if (ivf.second.size() == 1)
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


    if (parseStringField(is, "TextFontFamily", sf))
    {
        textFontFamily = sf.second;
    }
    else
    {
        return nullptr;
    }


    if (!parseEnumField<QFont::Style>(is, "TextFontStyle", fontStyleMap, style))
    {
        return nullptr;
    }

    if (!parseEnumField<QFont::Weight>(is, "TextFontWeight", fontWeightMap, weight))
    {
        return nullptr;
    }
    QFont* f = new QFont(QString(textFontFamily.c_str()), textPointSize);
    f->setStyle(style);
    f->setWeight(weight);
    return f;
}

void Shape::serializePen(ostream& os)
{
    serializeEnumField<Qt::GlobalColor>(os, "PenColor", colorSerializeMap, (Qt::GlobalColor)pen->color().value());
    vector<int> w{pen->width()};
    serializeIntVectorField(os, "PenWidth", w);
    serializeEnumField<Qt::PenStyle>(os, "PenStyle", penStyleSerializeMap, pen->style());
    serializeEnumField<Qt::PenCapStyle>(os, "PenCapStyle", penCapStyleSerializeMap, pen->capStyle());
    serializeEnumField<Qt::PenJoinStyle>(os, "PenJoinStyle", penJoinStyleSerializeMap, pen->joinStyle());
}

void Shape::serializeBrush(ostream& os)
{
    serializeEnumField<Qt::GlobalColor>(os, "BrushColor", colorSerializeMap, (Qt::GlobalColor)brush->color().value());
    serializeEnumField<Qt::BrushStyle>(os, "BrushStyle", brushStyleSerializeMap, brush->style());
}

void Shape::serializeFont(ostream& os)
{
    vector<int> v{font->pointSize()};
    serializeIntVectorField(os, "textPointSize", v);
    serializeStringField(os, "TextFontFamily", font->family().toStdString());
    serializeEnumField<QFont::Style>(os, "TextFontStyle", fontStyleSerializeMap, font->style());
    serializeEnumField<QFont::Weight>(os, "TextFontWeight", fontWeightSerializeMap, font->weight());

}

