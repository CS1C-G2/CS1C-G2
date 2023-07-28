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
    else
    {
        return nullptr;
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

        if (s == nullptr)
        {
            return nullptr;
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

