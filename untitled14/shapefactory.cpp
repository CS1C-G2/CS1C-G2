#include "shapefactory.h"
#include "shape.h"
#include "line.h"
#include "circle.h"
#include "rectangle.h"
#include "ellipse.h"
#include "polygon.h"
#include "polyline.h"
#include "square.h"
#include "text.h"
#include <fstream>


/*=======================================================================================
 * SHAPE FACTORY CLASS FUNCTIONS
 * =====================================================================================*/

Shape* ShapeFactory::createFromStream(std::istream& is)	//factory method
{
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
            s->SetShapeType(SHAPE_TYPES::LINE);
        }
        else if (shapeType.second.compare("Polyline") == 0)
        {
            s = new Polyline(shapeID);
            s->SetShapeType(SHAPE_TYPES::POLYLINE);
        }
        else if (shapeType.second.compare("Polygon") == 0)
        {
            s = new Polygon(shapeID);
            s->SetShapeType(SHAPE_TYPES::POLYGON);
        }
        else if (shapeType.second.compare("Rectangle") == 0)
        {
            s = new Rectangle(shapeID);
            s->SetShapeType(SHAPE_TYPES::RECTANGLE);
        }
        else if (shapeType.second.compare("Square") == 0)
        {
            s = new Square(shapeID);
            s->SetShapeType(SHAPE_TYPES::SQUARE);
        }
        else if (shapeType.second.compare("Ellipse") == 0)
        {
            s = new Ellipse(shapeID);
            s->SetShapeType(SHAPE_TYPES::ELLIPSE);
        }
        else if(shapeType.second.compare("Circle") == 0)
        {
            s = new Circle(shapeID);
            s->SetShapeType(SHAPE_TYPES::CIRCLE);
        }
        else if (shapeType.second.compare("Text") == 0)
        {
            s = new Text(shapeID);
            s->SetShapeType(SHAPE_TYPES::TEXT);
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
/*
vector<Shape*> parse(string fileName);

int main()
{
    vector<Shape*> shapes = parse("file:///C:/Users/suraj/Downloads/shapes.txt");

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
*/
