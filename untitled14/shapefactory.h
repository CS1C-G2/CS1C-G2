#ifndef PARSER_H
#define PARSER_H

#include <iostream>

class Shape;

/*=======================================================================================
 * SHAPEFACTORY CLASS
 * =====================================================================================*/

class ShapeFactory	//reads in shape type, based on type allocate the correct type of shape.
{
public:
    Shape* createFromStream(std::istream& is);	//factory method
};

#endif // PARSER_H
