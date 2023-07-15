enum SHAPE_TYPES { LINE, POLYLINE, POLYGON, RECTANGLE, SQUARE, ELLIPSE, CIRCLE, TEXT };

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