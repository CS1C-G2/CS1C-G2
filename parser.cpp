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



// FROM HERE DOWN IS YOUR CODE, ALL THE Q WHATEVER CLASSES ARE QT AND CAN BE INCLUDED

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
