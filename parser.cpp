#include "parser.h"

//Maps string to enum
/*===============================================================================*/
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
/*=================================================================================*/

//standalone function
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

//standalone function
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

/*=======================================================================================
 * SHAPE CLASS FUNCTIONS
 * =====================================================================================*/
QPen* Shape::serializePen(istream& is) // allocates a QPen and initializes from data read from the stream
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

QBrush* Shape::serializeBrush(istream& is) // allocates a QBrush and initializes from data read from the stream
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


QFont* Shape::serializeFont(istream& is)
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

/*=======================================================================================
 * LINE CLASS FUNCTIONS
 * =====================================================================================*/
bool Line::serializeShape(istream& is)
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


/*=======================================================================================
 * POLYLINE CLASS FUNCTIONS
 * =====================================================================================*/

bool Polyline::serializeShape(istream& is)
{
    bool validShape = true;
    // in here read in the shape stuffs from the stream
    IntVecField ivf;
    if(parseIntVectorField(is, "ShapeDimensions", ivf))
    {
        if(ivf.second.size() >= 4 && ivf.second.size() % 2 == 0)
        {
            points = ivf.second;

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

/*=======================================================================================
 * POLYGON CLASS FUNCTIONS
 * =====================================================================================*/

bool Polygon::serializeShape(istream& is)
{
    bool validShape = true;
    // in here read in the shape stuffs from the stream
    IntVecField ivf;
    if(parseIntVectorField(is, "ShapeDimensions", ivf))
    {
        if(ivf.second.size() >= 4 && ivf.second.size() % 2 == 0)
        {
            points = ivf.second;

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

/*=======================================================================================
 * RECTANGLE CLASS FUNCTIONS
 * =====================================================================================*/


bool Rectangle::serializeShape(istream& is)
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

/*=======================================================================================
 * SQUARE CLASS FUNCTIONS
 * =====================================================================================*/

bool Square::serializeShape(istream& is)
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

/*=======================================================================================
 * ELLIPSE CLASS FUNCTIONS
 * =====================================================================================*/

bool Ellipse::serializeShape(istream& is)
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

/*=======================================================================================
 * CIRCLE CLASS FUNCTIONS
 * =====================================================================================*/

bool Circle::serializeShape(istream& is)
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


/*=======================================================================================
 * TEXT CLASS FUNCTIONS
 * =====================================================================================*/

bool Text::serializeShape(istream& is)
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

    return validShape && font != nullptr;
}

/*=======================================================================================
 * SHAPE FACTORY CLASS FUNCTIONS
 * =====================================================================================*/

Shape* ShapeFactory::createFromStream(istream& is)	//factory method
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

//commented bc maybe dont need?
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
