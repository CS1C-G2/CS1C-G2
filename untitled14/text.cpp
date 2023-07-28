#include "text.h"
Text::Text(int id, int x1, int y1, int w, int l, QString textString, QFont* font, QPen* pen, Qt::AlignmentFlag textAlignment) :
    Shape(id, TEXT), x1{x1}, y1{y1}, w{w}, l{l}, textString{textString}, textAlignment{textAlignment} { }
Text::~Text() {}

void Text::draw() {
    update();
}

void Text::move(int x, int y) {
    x1 = x;
    y1 = y;
    draw();
}

double Text::area() {
    return l * w;
}

double Text::perimeter() {
    return (l * 2) + (w * 2);
}

void Text::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setFont(*font);
    painter->setPen(*pen);
    painter->drawText(x1, y1, w, l, textAlignment, textString);
}


void Text::setWidth(int width)
{
    w = width;
}

void Text::setLenth(int length)
{
    l = length;
}

QRectF Text::boundingRect() const {
    return QRectF(x1, y1, w, l);
}

void Text::setTextString(QString textString)
{
    this->textString = textString;
}

void Text::setTextColor(Qt::GlobalColor textColor)
{
    pen->setColor(textColor);
}

void Text::setTextAlignment(Qt::AlignmentFlag textAlignment)
{
    this->textAlignment = textAlignment;
}

void Text::setTextPointSize(int textPointSize)
{
    font->setPointSize(textPointSize);
}

void Text::setTextFontFamily(QString textFontFamily)
{
    font->setFamily(textFontFamily);
}

void Text::setTextFontStyle(QFont::Style textFontStyle)
{
    font->setStyle(textFontStyle);
}

void Text::setTextFontWeight(QFont::Weight textFontWeight)
{
    font->setWeight(textFontWeight);
}
bool Text::serializeShape(istream& is)
{
    bool validShape = true;
    // in here read in the shape stuffs from the stream
    IntVecField ivf;
    if (parseIntVectorField(is, "ShapeDimensions", ivf))
    {
        if (ivf.second.size() == 4)
        {
            x1 = ivf.second[0];
            y1 = ivf.second[1];
            w = ivf.second[2];
            l = ivf.second[3];

            StringField sf;
            if (parseStringField(is, "TextString", sf))
            {
                textString = sf.second.c_str();
            }
            else
            {
                validShape = false;
            }

            if (!parseEnumField<Qt::GlobalColor>(is, "TextColor", colorMap, textColor))
            {
                validShape = false;
            }

            if (!parseEnumField<Qt::AlignmentFlag>(is, "TextAlignment", alignmentFlagMap, textAlignment))
            {
                validShape = false;
            }

            font = serializeFont(is);
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

void Text::internalSerializeShape(ostream& os)
{
    serializeStringField(os, "ShapeType", "Text");
    std::vector<int> dims {x1, y1, w, l};
    serializeIntVectorField(os, "ShapeDimensions", dims);
    serializeStringField(os, "TextString", textString.toStdString());
    serializeEnumField<Qt::GlobalColor>(os, "TextColor", colorSerializeMap, textColor);
    serializeEnumField<Qt::AlignmentFlag>(os, "TextAlignment", alignmentFlagSerializeMap, textAlignment);
    serializeFont(os);
    
}
