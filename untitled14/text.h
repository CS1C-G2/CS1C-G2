#ifndef TEXT_H
#define TEXT_H
#include "shape.h"
class Text : public Shape, public QGraphicsItem
{
public:
    Text(int id, int x1, int y1, int w, int l, QString textString, QFont* font, QPen* pen, Qt::AlignmentFlag textAlignment);

    ~Text() override;

    void draw() override;

    void move(int x, int y) override;

    double area() override;

    double perimeter() override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    void setWidth(int width);

    void setLenth(int length);

    void setTextString(QString textString);

    void setTextColor(Qt::GlobalColor textColor);

    void setTextAlignment(Qt::AlignmentFlag textAlignment);

    void setTextPointSize(int textPointSize);

    void setTextFontFamily(QString textFontFamily);

    void setTextFontStyle(QFont::Style textFontStyle);

    void setTextFontWeight(QFont::Weight textFontWeight);

    QRectF boundingRect() const override;

private:
    int x1;
    int y1;
    int w;
    int l;
    QString textString;
    QFont* font;
    QPen* pen;
    Qt::AlignmentFlag textAlignment;
};
#endif // TEXT_H
