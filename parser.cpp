#include <iostream>
#include <fstream>
#include <limits>
#include <map>
#include "vector.cpp"

using myStd::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::map;
using std::streamsize;
using std::string;
using std::numeric_limits;

enum SHAPE_TYPES { LINE, POLYLINE, POLYGON, RECTANGLE, SQUARE, ELLIPSE, CIRCLE, TEXT };

namespace Qt
{
	enum GlobalColor
	{
		black,
		white,
		darkGray,
		gray,
		lightGray,
		red,
		green,
		blue,
		cyan,
		magenta,
		yellow,
		darkRed,
		darkGreen,
		darkBlue,
		darkCyan,
		darkMagenta,
		darkYellow,
		transparent,
	};

	enum PenStyle
	{
		NoPen,
		SolidLine,
		DashLine,
		DotLine,
		DashDotLine,
		DashDotDotLine,
	};

	enum PenCapStyle
	{
		FlatCap,
		SquareCap,
		RoundCap,
	};

	enum PenJoinStyle
	{
		MiterJoin,
		BevelJoin,
		RoundJoin,
		SvgMiterJoin,
	};

	enum BrushStyle
	{
		NoBrush,
		SolidPattern,
		Dense1Pattern,
		Dense2Pattern,
		Dense3Pattern,
		Dense4Pattern,
		Dense5Pattern,
		Dense6Pattern,
		Dense7Pattern,
		HorPattern,
		VerPattern,
		CrossPattern,
		BDiagPattern,
		FDiagPattern,
		DiagCrossPattern,
		LinearGradientPattern,
		ConicalGradientPattern,
		RadialGradientPattern,
		TexturePattern,
	};
}

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

class Shape
{
	int id;
	SHAPE_TYPES type;
};

class Line : public Shape
{
	public:
		Line(int, int, int, int, QPen*) {}
		~Line() {delete pen;}

	private:
		QPen* pen;
};

class Polyline : public Shape
{

};

class Polygon : public Shape
{

};
class Rectangle : public Shape
{

};
class Square : public Shape
{

};
class Ellipse : public Shape
{

};
class Circle : public Shape
{

};
class Text : public Shape
{

};

map<string, Qt::GlobalColor> colorMap {
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

map<string, Qt::PenStyle> penStyleMap {
	{"NoPen", Qt::NoPen},
	{"SolidLine", Qt::SolidLine},
	{"DashLine", Qt::DashLine},
	{"DotLine", Qt::DotLine},
	{"DashDotLine", Qt::DashDotLine},
	{"DashDotDotLine", Qt::DashDotDotLine},
};

map<string, Qt::PenCapStyle> penCapStyleMap {
	{"FlatCap", Qt::FlatCap},
	{"SquareCap", Qt::SquareCap},
	{"RoundCap", Qt::RoundCap},
};

map<string, Qt::PenJoinStyle> penJoinStyleMap {
	{"MiterJoin", Qt::MiterJoin},
	{"BevelJoin", Qt::BevelJoin},
	{"RoundJoin", Qt::RoundJoin},
	{"SvgMiterJoin", Qt::SvgMiterJoin},
};

map<string, Qt::BrushStyle> brushStyleMap {
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

vector<Shape*> parse(string fileName);
QPen* getPen(ifstream& inFile);
QBrush* getBrush(ifstream& inFile);

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
	inFile.open(fileName);

	vector<Shape*> shapes;

	int id = 0;
	string type;
	SHAPE_TYPES shapeType;

	inFile.ignore(numeric_limits<streamsize>::max(), ':');
	inFile >> id;

	inFile.ignore(numeric_limits<streamsize>::max(), ':');
	inFile >> type;

	// Not necessary prolly
	// if (type == "Line")
	// 	shapeType = LINE;
	// else if (type == "Polyline")
	// 	shapeType = POLYLINE;
	// else if (type == "Polygon")
	// 	shapeType = POLYGON;
	// else if (type == "Rectangle")
	// 	shapeType = RECTANGLE;
	// else if (type == "Square")
	// 	shapeType = SQUARE;
	// else if (type == "Ellipse")
	// 	shapeType = ELLIPSE;
	// else if (type == "Circle")
	// 	shapeType = CIRCLE;
	// else if (type == "Text")
	// 	shapeType = TEXT;

	if (type == "Line")
	{
		int x1 = 0;
		int y1 = 0;
		int x2 = 0;
		int y2 = 0;

		inFile.ignore(numeric_limits<streamsize>::max(), ':');
		inFile >> x1;
		inFile.ignore();

		inFile >> y1;
		inFile.ignore();

		inFile >> x2;
		inFile.ignore();

		inFile >> y2;
		inFile.ignore();

		QPen* pen = getPen(inFile);
		
		shapes.push_back(new Line(x1, y1, x2, y2, pen));
	}
	else if (type == "Polyline")
	{

	}
	else if (type == "Polygon")
	{
		int x = 0;
		int y = 0;

		// QList<QPoint> points;

		inFile.ignore(numeric_limits<streamsize>::max(), ':');
        while (inFile.peek() != '\n')
        {
            inFile >> x;
            inFile.ignore();
            inFile >> y;
			inFile.ignore();

			cout << x << " " << y << endl;

			// points.push_back(QPoint(x, y));
        }

		// QPen* pen = getPen(inFile);

		// shapes.push_back(new Polygon(points, pen));
	}
	else if (type == "Rectangle" || type == "Square")
	{
		int x1 = 0;
		int y1 = 0;
		int x2 = 0;
		int y2 = 0;

		inFile.ignore(numeric_limits<streamsize>::max(), ':');
		inFile >> x1;
		inFile.ignore();

		inFile >> y1;
		inFile.ignore();

		inFile >> x2;
		inFile.ignore();

		inFile >> y2;
		inFile.ignore();

		QPoint topLeft(x1, y1);
		QPoint bottomRight(x2, y2);

		QPen* pen = getPen(inFile);
		QBrush* brush = getBrush(inFile);

		// shapes.push_back(new Rectangle(new QRect(topLeft, bottomRight), pen, brush));
	}
	else if (type == "Ellipse")
		shapeType = ELLIPSE;
	else if (type == "Circle")
		shapeType = CIRCLE;
	else if (type == "Text")
	{
		int x1 = 0;
		int y1 = 0;
		int x2 = 0;
		int y2 = 0;

		string text;
		string color;
		string alignment;
		int pointSize = 0;
		string fontFamily;
		string fontStyle;
		string fontWeight;

		inFile.ignore(numeric_limits<streamsize>::max(), ':');
		inFile >> x1;
		inFile.ignore();

		inFile >> y1;
		inFile.ignore();

		inFile >> x2;
		inFile.ignore();

		inFile >> y2;
		inFile.ignore();


	}
	
	

	inFile.close();

	return shapes;
}

QPen* getPen(ifstream& inFile)
{
	string color;
	int width;
	string style;
	string capStyle;
	string joinStyle;

	Qt::GlobalColor penColor = Qt::black;
	Qt::PenStyle penStyle = Qt::SolidLine;
	Qt::PenCapStyle penCapStyle = Qt::SquareCap;
	Qt::PenJoinStyle penJoinStyle = Qt::BevelJoin;

	inFile.ignore(numeric_limits<streamsize>::max(), ':');
	inFile >> color;

	inFile.ignore(numeric_limits<streamsize>::max(), ':');
	inFile >> width;

	inFile.ignore(numeric_limits<streamsize>::max(), ':');
	inFile >> style;

	inFile.ignore(numeric_limits<streamsize>::max(), ':');
	inFile >> capStyle;

	inFile.ignore(numeric_limits<streamsize>::max(), ':');
	inFile >> joinStyle;
	inFile.ignore();

	if (colorMap.contains(color))
		penColor = colorMap[color];

	if (penStyleMap.contains(style))
		penStyle = penStyleMap[style];

	if (penCapStyleMap.contains(capStyle))
		penCapStyle = penCapStyleMap[capStyle];

	if (penJoinStyleMap.contains(joinStyle))
		penJoinStyle = penJoinStyleMap[joinStyle];

	return new QPen(penColor, width, penStyle, penCapStyle, penJoinStyle);
}

QBrush* getBrush(ifstream& inFile)
{
	string color;
	string style;

	Qt::GlobalColor brushColor = Qt::black;
	Qt::BrushStyle brushStyle = Qt::SolidPattern;

	inFile.ignore(numeric_limits<streamsize>::max(), ':');
	inFile >> color;
	
	inFile.ignore(numeric_limits<streamsize>::max(), ':');
	inFile >> style;
	inFile.ignore();

	if (colorMap.contains(color))
		brushColor = colorMap[color];

	if (brushStyleMap.contains(style))
		brushStyle = brushStyleMap[style];

	return new QBrush(brushColor, brushStyle);
}