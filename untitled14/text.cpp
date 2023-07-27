#include "text.h"
Text::Text(int id, int x1, int y1, int w, int l, QString textString, QFont* font, QPen* pen, Qt::AlignmentFlag textAlignment) :
    Shape(id, TEXT), x1{x1}, y1{y1}, w{w}, l{l}, textString{textString}, font{font}, pen{pen}, textAlignment{textAlignment} { }
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
QRectF Text::boundingRect() const
{
    return QRectF();
}
