#ifndef TEXT_H
#define TEXT_H
#include "shape.h"
class Text : public Shape
{
public:
    Text(int id, int x1, int y1, int w, int l, QString textString, QFont* font, QPen* pen, Qt::AlignmentFlag textAlignment);
    Text(int id) : Shape(id) {}
    virtual bool serializeShape(istream& is) override;
    ~Text() override;
    void draw() override;
    void move(int x, int y) override;
    double area() override;
    double perimeter() override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void setWidth(int width);
    void setLenth(int length);
    QRectF boundingRect() const override;
    void setTextString(QString textString);
    void setTextColor(Qt::GlobalColor textColor);
    void setTextAlignment(Qt::AlignmentFlag textAlignment);
    void setTextPointSize(int textPointSize);
    void setTextFontFamily(QString textFontFamily);
    void setTextFontStyle(QFont::Style textFontStyle);
    void setTextFontWeight(QFont::Weight textFontWeight);


private:
    int x1;
    int y1;
    int w;
    int l;
    QString textString;
    string textFont;
    Qt::GlobalColor textColor;
    Qt::AlignmentFlag textAlignment;
    virtual void internalSerializeShape(ostream& os) override;
};
#endif // TEXT_H
